# BNCSUtil
## Preface
**BNCSUtil** is the **B**attle.**N**et **C**hat **S**ervice **Util**ity which
aids applications trying to logon to Classic Battle.net&trade; using the binary
protocol. Specifically, BNCSUtil has functions that help with the cryptography
of game versions, keys, and passwords.

## Installing
Simply place the `.so` or `.dll` file in the same directory as the application
that wishes to use it. If this does not work, install the file into the system
library directory.

### Windows
Copy the file to:

```
C:\Windows\System32
```

### Linux
If you just have the `.so` file, copy it to:

```
/usr/lib/
```

And run:

```
sudo ldconfig
```

If you have just compiled from source, run this instead:

```
sudo make install
```

## Building
### Windows
The official build of BNCSUtil for Windows is produced using Visual Studio 2005
using the solution file in the `vc8_build` folder.

BNCSUtil requires GMP.

### Linux
To build:
```
cd src/bncsutil
make clean
make
```

If you are having build related issues, ensure that:

- You have the `gcc` package installed.
- You have the `glibc` development package installed.
- You have the `gmp` development package installed.
