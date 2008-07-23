AUTOMAKE_OPTIONS        = gnu
AM_CPPFLAGS             = -I@ROOTINCDIR@
lib_LTLIBRARIES         = libbncsutil.la
nobase_include_HEADERS  = bncsutil/bncsutil.h      \
                          bncsutil/cdkeydecoder.h  \
                          bncsutil/decodekey.h     \
                          bncsutil/libinfo.h       \
                          bncsutil/nls.h           \
                          bncsutil/sha1.h          \
                          bncsutil/bsha1.h         \
                          bncsutil/checkrevision.h \
                          bncsutil/file.h          \
                          bncsutil/mutil.h         \
                          bncsutil/oldauth.h       \
                          bncsutil/stack.h         \
                          bncsutil/buffer.h        \
                          bncsutil/debug.h         \
                          bncsutil/keytables.h     \
                          bncsutil/mutil_types.h   \
                          bncsutil/pe.h

libbncsutil_la_SOURCES  = bncsutil/nls.c              \
                          bncsutil/pe.c               \
                          bncsutil/sha1.c             \
                          bncsutil/stack.c            \
                          bncsutil/bsha1.cpp          \
                          bncsutil/checkrevision.cpp  \
                          bncsutil/file.cpp           \
                          bncsutil/oldauth.cpp        \
                          bncsutil/cdkeydecoder.cpp   \
                          bncsutil/decodekey.cpp      \
                          bncsutil/libinfo.cpp 

libbncsutil_la_LDFLAGS = -version-info 0:0:0
