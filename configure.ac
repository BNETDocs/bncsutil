AC_INIT([bncsutil], [1.3.2], [bugs@example.com])

AM_INIT_AUTOMAKE([-Wall -Werror foreign])
AM_PROG_LIBTOOL

AC_PROG_INSTALL

AC_LANG_C
AC_PROG_CC
AC_PROG_CXX
AC_PROG_INSTALL
AC_PROG_MAKE_SET

AC_HEADER_STDC

AC_CHECK_LIB(gmp, __gmpz_init,, AC_MSG_ERROR([
bncsutil requires libgmp; see http://gmplib.org]))

[echo -n "checking for little or big endian... " ]
AC_TRY_RUN([
#include <sys/types.h>
int main()
{
	uint16_t  s   = 1;
	uint16_t* ptr = &s;
	uint8_t   n   = *((uint8_t*)ptr);
	return n;     
}

]
, AC_DEFINE([BIGENDIAN], [1], [Define to 1 if system is big endian])
  [echo "big"]
, AC_DEFINE([LITTLEENDIAN], [1], [Define to 1 if system is little endian])
  [echo "little"] 
)

AC_CONFIG_HEADERS([config.h])
AC_CONFIG_FILES([
	Makefile
	src/Makefile
])

AC_OUTPUT
