# BNCSUtil
## Preface
**BNCSUtil** is the **B**attle.**N**et **C**hat **S**ervice **Util**ity which
aids applications trying to logon to Classic Battle.net&trade; using the binary
protocol. Specifically, BNCSUtil has functions that help with the cryptography
of game versions, keys, and passwords.

BNCSUtil was originally written by Eric Naeseth (shadypalm88) and has since
been maintained over the course of several years by the open source Battle.net community.

## Usage
Add `bncsutil.h` to your include directory and link against `bncsutil.lib` or `libbncsutil.so`.

## Building
CMake is used to generate platform specific build files. The only external dependency is GMP (The GNU Multiple Precision Arithmetic Library ).
It can be installed with a package manager from any major Linux distro. Debian example: `sudo apt-get install libgmp10`.

### Windows

#### GMP
If you are suing an older toolchain like VS 2005 or 2008, the GMP lib and header file is already included for you in `depends/include` and `depends/lib`. You can skip this step.
For newer versions of Visual Studio we recommend to use MPIR library instead which is a drop-in replacement for GMP with better Windows support.
1. Go to http://mpir.org/ and download the latest source archive.
2. Open the VS solution file depending on which version you use, for example build.vc14 for VS 2015.
3. Make a Release build of `lib_mpir_gc` project. This produces `mpir.lib` and `mpir.h` in `build.vc14\lib_mpir_gc\Win32\Release`. Copy the header file to `depends/include` and library to `depends/lib`.

#### VS build
1. In root bncsutil folder run `cmake -G "Visual Studio 14 2015" -B./build -H./` if you used GMP or `cmake -G "Visual Studio 14 2015" -B./build -H./ -DUSE_MPIR=1` if you used MPIR in previous step. Change the Visual Studio version as needed.
2. CMake will generate sln file in ./build. Open it and build the library.

### Linux
1. Install GMP with the package manager. Also install all the necessary deveklopment tools (gcc, make or build-essential package on Debian).
2. Run `cmake -G "Unix Makefiles" -B./build -H./`.
3. `cd build && make && make install`.