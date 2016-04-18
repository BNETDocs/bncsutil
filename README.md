# BNCSUtil

## How to Compile

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

Note that to use autoreconf you will need to have GNU autotools installed.
