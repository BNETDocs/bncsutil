# BNCSUtil
## Preface
**BNCSUtil** is the **B**attle.**N**et **C**hat **S**ervice **Util**ity which
aids applications trying to logon to Battle.net&trade; v1 using the binary
protocol. Specifically, BNCSUtil has functions that help with the cryptography
of game versions, keys, and passwords.

## Installing
Simply place the .so or .dll file in the same directory as the application that
wishes to use it. If this does not work, install the file into the system
library directory.

On Windows, this directory is:
```
C:\Windows\System32
```

On Linux, this directory is:
```
/usr/lib/
```

## Building
### Windows
The official build of BNCSUtil for Windows is produced using Visual Studio 2005
using the solution file in the `vc8_build` folder. The `vc7_build` is no longer
officially used or supported.

BNCSUtil requires GMP.

### Linux
To build:
```
./configure
make
make install
```

If you have a fresh checkout or are having build-related issues, run the
following to (re)generate the configure script:
```
autoreconf -if
```

Note that to use `autoreconf` you will need to have GNU `autotools` installed.
