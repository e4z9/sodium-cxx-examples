add_executable(airline1 airline1.cpp)
target_link_libraries(airline1 SodiumCxx Qt5::Widgets SQtWidgets)

add_executable(airline2 airline2.cpp)
target_link_libraries(airline2 SodiumCxx Qt5::Widgets SQtWidgets)

add_executable(clearfield clearfield.cpp)
target_link_libraries(clearfield SodiumCxx Qt5::Widgets SQtWidgets)

add_executable(label label.cpp)
target_link_libraries(label SodiumCxx Qt5::Widgets SQtWidgets)

add_executable(reverse reverse.cpp)
target_link_libraries(reverse SodiumCxx Qt5::Widgets SQtWidgets)

add_executable(gamechat gamechat.cpp)
target_link_libraries(gamechat SodiumCxx Qt5::Widgets SQtWidgets)

add_executable(redgreen redgreen.cpp)
target_link_libraries(redgreen SodiumCxx Qt5::Widgets SQtWidgets)

add_executable(translate translate.cpp)
target_link_libraries(translate SodiumCxx Qt5::Widgets SQtWidgets)

add_executable(spinner spinner.cpp)
target_link_libraries(spinner SodiumCxx Qt5::Widgets SQtWidgets)

add_executable(add add.cpp)
target_link_libraries(add SodiumCxx Qt5::Widgets SQtWidgets)

add_executable(spinme spinme.cpp sqspinner.cpp sqspinner.h)
target_link_libraries(spinme SodiumCxx Qt5::Widgets SQtWidgets)

add_executable(formvalidation formvalidation.cpp sqspinner.cpp sqspinner.h)
target_link_libraries(formvalidation SodiumCxx Qt5::Widgets SQtWidgets)

add_executable(noglitches noglitches.cpp)
target_link_libraries(noglitches SodiumCxx)

add_executable(sametrans sametrans.cpp)
target_link_libraries(sametrans SodiumCxx)

add_executable(lookup lookup.cpp)
target_link_libraries(lookup SodiumCxx Qt5::Widgets Qt5::Network SQtWidgets)

add_executable(promise1 promise1.cpp)
target_link_libraries(promise1 SodiumCxx)
