# Examples for sodium-cxx

Sodium-cxx is the C++ variant of the Sodium framework for Functional Reactive Programming (FRP).
There is a great book `Functional Reactive Programming` from Stephen Blackheath and
Anthony Jones, which includes many examples based on the Java variant of Sodium.
This project aims to translate these examples to C++.

## How to build

### Sodium-cxx requires Boost. E.g. on macOS you can install Boost with
```
brew install boost
```

### Many of the sodium-cxx-examples require Qt. E.g. on macOS you can install Qt with
```
brew install qt
```
or you can use the official binary installers from
[the Qt Project](https://download.qt.io/official_releases/qt).

### Get, build and install sodium-cxx
```
git clone https://github.com/SodiumFRP/sodium-cxx.git
cmake -B sodium-cxx/build -DCMAKE_INSTALL_PREFIX="$PWD/sodium-cxx/install" -DCMAKE_BUILD_TYPE=Release -G Ninja sodium-cxx
cmake --build sodium-cxx/build
cmake --install sodium-cxx/build
```
If you installed Boost or Qt in a non-standard location,
you need to add `-DCMAKE_PREFIX_PATH="/path/to/boost;/path/to/qt"` to the first `cmake` call.

### Build the examples

```
cd /to/this/directory
cmake -B build -DCMAKE_PREFIX_PATH=/path/to/sodium-cxx/install -G Ninja .
cmake --build build
```
If you installed Boost or Qt in a non-standard location, you need to change the first `cmake` call
to include the path to Boost or Qt
`-DCMAKE_PREFIX_PATH="/path/to/sodium-cxx/install;/path/to/boost;/path/to/qt"`
to the first `cmake` call.
