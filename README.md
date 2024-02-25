# BNCSUtil

[![GitHub Workflow Status (branch)](https://img.shields.io/github/actions/workflow/status/BNETDocs/bncsutil/cmake.yml?branch=master&style=flat)](https://github.com/BNETDocs/bncsutil/actions?query=workflow%3ACMake)
[![GitHub top language](https://img.shields.io/github/languages/top/BNETDocs/bncsutil?style=flat)](https://github.com/BNETDocs/bncsutil)
![GitHub code size in bytes](https://img.shields.io/github/languages/code-size/BNETDocs/bncsutil?style=flat)
[![License Badge](https://img.shields.io/github/license/BNETDocs/bncsutil?style=flat)](https://github.com/BNETDocs/bncsutil/blob/master/COPYING)
[![GitHub release (latest SemVer including pre-releases)](https://img.shields.io/github/v/release/BNETDocs/bncsutil?include_prereleases&label=latest%20release&style=flat)](https://github.com/BNETDocs/bncsutil/releases/latest)
[![GitHub All Releases](https://img.shields.io/github/downloads/BNETDocs/bncsutil/total?style=flat)](https://github.com/BNETDocs/bncsutil/releases/latest)

**BNCSUtil** is the **B**attle.**N**et **C**hat **S**ervice **Util**ity which
aids applications trying to logon to Classic Battle.net&trade; using the binary
protocol. Specifically, BNCSUtil has functions that help with the cryptography
of game versions, keys, and passwords.

BNCSUtil was originally written by Eric Naeseth (shadypalm88) and has since
been maintained over the course of several years by the open source Battle.net community.

# Usage
`#include <bncsutil/bncsutil.h>` and link against `bncsutil.lib` or `libbncsutil.so`.

# Building

To force a specific build (32bit or 64bit) add `-DCMAKE_GENERATOR_PLATFORM=x86` or `-DCMAKE_GENERATOR_PLATFORM=x64` to CMake flags.

Change `BUILD_SHARED_LIBS` to build the library as static or shared.

## Windows Visual Studio 2022

Conan is used to install dependencies. GMP can't be installed as a shared library due to a bug. Mpir dependency option will be re-introduced once it is uploaded to conan index v2 (MR pending).

In `cmd` or Visual Studio dev console run:

### amd64
```
"C:/Program Files/Microsoft Visual Studio/2022/Community/VC/Auxiliary/Build/vcvarsall.bat" x64
conan install . -of build -s build_type=Release -o *:shared=False --build=missing
cd build
.\conanbuild.bat
cmake .. -G "Visual Studio 17 2022" -DCMAKE_TOOLCHAIN_FILE=conan_toolchain.cmake -DBUILD_SHARED_LIBS=1
cmake --build . --config Release
```

### x86
```
"C:/Program Files/Microsoft Visual Studio/2022/Community/VC/Auxiliary/Build/vcvarsall.bat" x86
conan install . -of build -s build_type=Release -s:h arch=x86 -o *:shared=False --build=missing
cd build
.\conanbuild.bat
cmake .. -G "Visual Studio 17 2022" -DCMAKE_GENERATOR_PLATFORM=x86 -DCMAKE_TOOLCHAIN_FILE=conan_toolchain.cmake -DBUILD_SHARED_LIBS=1
cmake --build . --config Release
```

Alternatively open `build/bncsutil.sln` and build from Visual Studio.

## Linux

### Using system dependencies
Install `libgmp-dev` on deb distros or `gmp-devel` on rpm distros. For 32bit builds, CMake will not warn you if you are missing 32bit glibc and GMP, you must install them manually first (CentOS/Fedora: `glibc-devel.i686` and `gmp-devel.i686`).

```
cmake -G "Unix Makefiles" -B./build
cd build
cmake --build . --target install --config Release
```

### Using conan
If you are using pyenv or building python3 from source, make sure you have `libbz2-dev` and `liblzma-dev` installed first or conan will fail to unpack dependencies.

```
conan install . -of build -s build_type=Release --build=missing
cd build
./conanbuild.sh
cmake .. -G "Unix Makefiles" -DCMAKE_TOOLCHAIN_FILE=conan_toolchain.cmake -DUSE_SYSTEM_LIBS=0
cmake --build . --target install --config Release
```

## .deb and .rpm packages
After invoking CMake, cd to build folder and generate them with `cpack -G "DEB"` and `cpack -G "RPM"`.
You can then use `gdebi` to do a local install of .deb with automatic dependency resolution or `yum localinstall` on rpm distros. For dnf it's `dnf install <name>.rpm`.

Note that this is a "development" package which also includes header files.

Library installs to `/usr/local/lib`, include files in `/usr/local/include/bncsutil`.

Packages are also available for download from github releases built on Debian Bookworm and Fedora latest.

# Development with CLion
1. Run conan from cli as per instructions
2. Open the project
3. Tools -> CMake -> Change Project Root -> build
4. Settings -> Build, Execution, Deployment -> CMake -> Add at least this cmake option: -DCMAKE_TOOLCHAIN_FILE=conan_toolchain.cmake

