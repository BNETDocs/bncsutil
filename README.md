# BNCSUtil

![GitHub top language](https://img.shields.io/github/languages/top/BNETDocs/bncsutil)
![License Badge](https://img.shields.io/github/license/BNETDocs/bncsutil)
![GitHub Workflow Status (master)](https://img.shields.io/github/workflow/status/BNETDocs/bncsutil/CMake/master)
![GitHub stars](https://img.shields.io/github/stars/BNETDocs/bncsutil?style=social)

**BNCSUtil** is the **B**attle.**N**et **C**hat **S**ervice **Util**ity which
aids applications trying to logon to Classic Battle.net&trade; using the binary
protocol. Specifically, BNCSUtil has functions that help with the cryptography
of game versions, keys, and passwords.

BNCSUtil was originally written by Eric Naeseth (shadypalm88) and has since
been maintained over the course of several years by the open source Battle.net community.

## Usage
Add `bncsutil.h` to your include directory and link against `bncsutil.lib` or `libbncsutil.so`.

## Building

To force a specific build (32bit or 64bit) add `-DCMAKE_GENERATOR_PLATFORM=x86` or `-DCMAKE_GENERATOR_PLATFORM=x64` to CMake flags. 

### Windows Visual Studio 2019

Version 2019 has compiler version 16, 2015 has compiler version 14.

Change `-o *:shared` option if you want to link static or dynamic dependencies.

Change `BUILD_SHARED_LIBS` to build the library as static or shared.

```
conan install . -if ./build -s compiler.version=16 -s arch=x86_64 -o *:shared=True
cmake -G "Visual Studio 16 2019" -B./build -DBUILD_SHARED_LIBS=1 -DCMAKE_GENERATOR_PLATFORM=x64
```

### Linux

#### Using system dependencies
Instead of using conan you can link against system provided gmp. Install `libgmp-dev` on deb distros or `gmp-devel` on rpm distros. For 32bit builds, CMake will not warn you if you are missing 32bit glibc and GMP, you must install them manually first (CentOS/Fedora: `glibc-devel.i686` and `gmp-devel.i686`).

```
cmake -G "Unix Makefiles" -B./build
cd build && make && make install
```

#### Using conan
If you are using pyenv or building python3 from source, make sure you have the following packages installed first:
```
sudo apt-get install libbz2-dev liblzma-dev
```

```
conan install . -of build -s build_type=Release --build=missing
cmake -G "Unix Makefiles" -B./build -DUSE_SYSTEM_LIBS=0
cd build && make && make install
```

## Building .deb and .rpm packages
After invoking CMake, cd to build folder and generate them with `cpack -G "DEB"` and `cpack -G "RPM"`.
You can then use `gdebi` to do a local install of .deb with automatic dependency resolution or `yum localinstall` on rpm distros. For dnf it's `dnf install <name>.rpm`.

Note that this is a "devel" package which also includes header files.

Library installs go to `/usr/lib`, include files in `/usr/include/bncsutil`. 