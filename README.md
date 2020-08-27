# BNCSUtil
[![Build Status](https://travis-ci.org/BNETDocs/bncsutil.svg?branch=master)](https://travis-ci.org/BNETDocs/bncsutil)

**BNCSUtil** is the **B**attle.**N**et **C**hat **S**ervice **Util**ity which
aids applications trying to logon to Classic Battle.net&trade; using the binary
protocol. Specifically, BNCSUtil has functions that help with the cryptography
of game versions, keys, and passwords.

BNCSUtil was originally written by Eric Naeseth (shadypalm88) and has since
been maintained over the course of several years by the open source Battle.net community.

## Usage
Add `bncsutil.h` to your include directory and link against `bncsutil.lib` or `libbncsutil.so`.

## Building with conan and CMake
Conan will automatically install mpir on Windows and gmp on non-Windows platforms.

To force a specific build (32bit or 64bit) add `-DCMAKE_GENERATOR_PLATFORM=x86` or `-DCMAKE_GENERATOR_PLATFORM=x64` to CMake flags. 

### Windows Visual Studio 2019

Static
```
conan install . -if ./build -s compiler.version=16 -s arch=x86_64 -o *:shared=False
cmake -G "Visual Studio 16 2019" -B./build -DBUILD_SHARED_LIBS=0 -DCMAKE_GENERATOR_PLATFORM=Win32
```

Shared
```
conan install . -if ./build -s compiler.version=16 -s arch=x86_64 -o *:shared=True
cmake -G "Visual Studio 16 2019" -B./build -DBUILD_SHARED_LIBS=1 -DCMAKE_GENERATOR_PLATFORM=x64
```

### Windows Visual Studio 2015

Shared
```
conan install . -if ./build -s compiler.version=14 -s arch=x86_64 -o *:shared=True
cmake -G "Visual Studio 14 2015" -B./build -DBUILD_SHARED_LIBS=1 -DCMAKE_GENERATOR_PLATFORM=x64
```


Open `.sln` in `build` directory and build from Visual Studio.

### Linux
```
conan install . -if ./build
cmake -G "Unix Makefiles" -B./build
cd build && make && make install
```

## Building using system dependencies
Instead of using conan you can link against system provided gmp. Install `libgmp-dev` on deb distros or `gmp-devel` on rpm distros. For 32bit builds, CMake will not warn you if you are missing 32bit glibc and GMP, you must install them manually first (CentOS/Fedora: `glibc-devel.i686` and `gmp-devel.i686`).

```
cmake -G "Unix Makefiles" -B./build
cd build && make && make install
```

## Building .deb and .rpm packages
After invoking CMake, cd to build folder and generate them with `cpack -G "DEB"` and `cpack -G "RPM"`.
You can then use `gdebi` to do a local install of .deb with automatic dependency resolution or `yum localinstall` on rpm distros. For dnf it's just `dnf install <name>.rpm`.

## Hosted Linux repositories
DEB and RPM repositories are maintained with best effort.

### Debian 8 and 9 (amd64)
 1. To `/etc/apt/sources.list` add:

#### 9
```
#apt.xpam.pl
deb http://apt.xpam.pl/debian9/ bnetdocs-stretch main
```
#### 8
```
#apt.xpam.pl
deb http://apt.xpam.pl/debian8/ bnetdocs-jessie main
```

 2. Add GPG key: `wget -qO - https://apt.xpam.pl/xpam.pl-pubkey.asc | sudo apt-key add -`
 3. Update and install: `sudo apt-get update && sudo apt-get install bncsutil`


### Centos 7
```
yum -y install yum-utils
yum-config-manager --add-repo https://centos7.rpm.xpam.pl
yum-config-manager --enable https://centos7.rpm.xpam.pl
rpm --import https://centos7.rpm.xpam.pl/xpam.pl-pubkey.asc
yum -y install bncsutil
```
### Centos 6
```
yum -y install yum-utils
yum-config-manager --add-repo https://centos6.rpm.xpam.pl
yum-config-manager --enable https://centos6.rpm.xpam.pl
rpm --import https://centos6.rpm.xpam.pl/xpam.pl-pubkey.asc
yum -y install bncsutil
```
