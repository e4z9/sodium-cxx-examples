#include <sqlineedit.h>
#include <sqpushbutton.h>
#include <sqtextedit.h>

#include <sodium/sodium.h>

#include <QApplication>
#include <QHBoxLayout>
#include <QTcpSocket>
#include <QThread>
#include <QWidget>

using namespace sodium;

// Chapter 11.1

template<typename A, typename B>
std::pair<stream<B>, stream<bool>> isBusy(const std::function<stream<B>(stream<A>)> &action,
                                          const stream<A> &sIn)
{
    const stream<B> sOut = action(sIn);
    const stream<bool> sBusy = sOut.map([](const B &) { return false; })
                                   .or_else(sIn.map([](const A &) { return true; }));
    return {sOut, sBusy};
}

static QString readLine(QTcpSocket &socket)
{
    while (!socket.canReadLine())
        socket.waitForReadyRead(50);
    return QString::fromUtf8(socket.readLine());
}

class LookupThread : public QThread
{
public:
    LookupThread(const QString &wrd, const stream_sink<boost::optional<QString>> &sDefinition)
        : wrd(wrd)
        , sDefinition(sDefinition)
    {}

    void run() override
    {
        boost::optional<QString> def;
        QTcpSocket socket;
        socket.connectToHost("dict.org", 2628);
        if (socket.waitForConnected(5000)) {
            const auto greeting = readLine(socket);
            socket.write(QString("DEFINE ! %1\n").arg(wrd).toUtf8());
            socket.flush();
            QString line = readLine(socket);
            if (line.startsWith("150"))
                line = readLine(socket);
            if (line.startsWith("151")) {
                QString result;
                while (true) {
                    line = readLine(socket).replace("\r\n", "");
                    if (line == ".")
                        break;
                    result += line + "\n";
                }
                if (!result.isEmpty())
                    def = boost::make_optional(result);
            }
            socket.close();
        }
        sDefinition.send(def);
    }

private:
    QString wrd;
    stream_sink<boost::optional<QString>> sDefinition;
};

static stream<boost::optional<QString>> lookup(const stream<QString> &sWord)
{
    stream_sink<boost::optional<QString>> sDefinition;
    const auto unlisten = sWord.listen([sDefinition](const QString &wrd) {
        auto thread = new LookupThread(wrd, sDefinition);
        // thread is allocated on heap, so make sure it is deleted after finishing
        QObject::connect(thread, &QThread::finished, thread, &QObject::deleteLater);
        thread->start();
    });
    return sDefinition.add_cleanup(unlisten);
}

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    QWidget window;

    {
        transaction t;
        auto word = new SQLineEdit("");
        cell_loop<bool> enabled;
        auto button = new SQPushButton("Look Up", enabled);
        const stream<QString> sWord = button->sClicked().snapshot(word->text());
        stream<boost::optional<QString>> sResult;
        stream<bool> sBusy;
        std::tie(sResult, sBusy) = isBusy<QString, boost::optional<QString>>(lookup, sWord);
        const stream<QString> sDefinition = sResult.map(
            [](const boost::optional<QString> &r) { return r.get_value_or("ERROR!"); });

        // if busy fires with "true", send "Looking up" to the output area
        const stream<QString> sBusyText = sBusy.filter([](bool b) { return b; }).map([](bool) {
            return QString("Looking up...");
        });
        const stream<QString> sOutput = sBusyText.or_else(
            sDefinition.map([](QString s) { return "<pre>" + s + "</pre>"; }));
        enabled.loop(sBusy.map([](bool b) { return !b; }).hold(true));
        auto outputArea = new SQTextEdit(sOutput, "", enabled);
        outputArea->setReadOnly(true);

        // GUI layout
        auto layout = new QVBoxLayout;
        window.setLayout(layout);
        layout->addWidget(word);
        layout->addWidget(button);
        layout->addWidget(outputArea, 10);
    }

    window.setGeometry(100, 100, 500, 500);
    window.show();
    return app.exec();
}
