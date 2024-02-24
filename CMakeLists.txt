cmake_minimum_required(VERSION 3.25)
project(bncsutil)

set(CMAKE_MODULE_PATH ${CMAKE_BINARY_DIR} "${PROJECT_SOURCE_DIR}/CMake/Modules")
message(${CMAKE_BINARY_DIR})

SET(VERSION_MAJOR "1")
SET(VERSION_MINOR "4")
SET(VERSION_PATCH "2")

add_library(bncsutil SHARED)

set(HEADERS
    "src/bncsutil/bncsutil.h"
    "src/bncsutil/bsha1.h"
    "src/bncsutil/buffer.h"
    "src/bncsutil/cdkeydecoder.h"
    "src/bncsutil/checkrevision.h"
    "src/bncsutil/decodekey.h"
    "src/bncsutil/file.h"
    "src/bncsutil/keytables.h"
    "src/bncsutil/libinfo.h"
    "src/bncsutil/ms_stdint.h"
    "src/bncsutil/mutil.h"
    "src/bncsutil/mutil_types.h"
    "src/bncsutil/nls.h"
    "src/bncsutil/oldauth.h"
    "src/bncsutil/pe.h"
    "src/bncsutil/sha1.h"
    "src/bncsutil/stack.h"
)

set(SOURCES
    "src/bncsutil/bsha1.cpp"
    "src/bncsutil/cdkeydecoder.cpp"
    "src/bncsutil/checkrevision.cpp"
    "src/bncsutil/decodekey.cpp"
    "src/bncsutil/file.cpp"
    "src/bncsutil/libinfo.cpp"
    "src/bncsutil/nls.c"
    "src/bncsutil/oldauth.cpp"
    "src/bncsutil/pe.c"
    "src/bncsutil/sha1.c"
    "src/bncsutil/stack.c"
)

target_sources(bncsutil PRIVATE ${SOURCES} ${HEADERS})

if (WIN32)
    set(USE_SYSTEM_LIBS 0)
else()
    set(USE_SYSTEM_LIBS 1)
endif()

if (CMAKE_GENERATOR_PLATFORM EQUAL "x86")
    set_target_properties(bncsutil PROPERTIES COMPILE_FLAGS "-m32" LINK_FLAGS "-m32")
    MESSAGE(STATUS "Excluding 64bit library paths from search.")
    set_property(GLOBAL PROPERTY FIND_LIBRARY_USE_LIB64_PATHS OFF)
    set(ARCH_DEB i386)
    set(ARCH_RPM i686)
elseif (CMAKE_GENERATOR_PLATFORM EQUAL "x64")
    set_target_properties(bncsutil PROPERTIES COMPILE_FLAGS "-m64" LINK_FLAGS "-m64")
    set(ARCH_DEB amd64)
    set(ARCH_RPM x86_64)
else()
    set(ARCH_DEB amd64)
    set(ARCH_RPM x86_64)
endif()

if (USE_SYSTEM_LIBS)
    message("Using system dependencies")
    find_package(GMP REQUIRED)
    target_include_directories(bncsutil PRIVATE src ${GMP_INCLUDE_DIR})
    target_link_libraries(bncsutil ${GMP_LIBRARIES})
else()
    message("Using conan dependencies")
    find_package(gmp REQUIRED)
    target_include_directories(bncsutil PRIVATE src gmp::gmp)
    target_link_libraries(bncsutil PRIVATE gmp::gmp)
endif()

set_target_properties(bncsutil PROPERTIES OUTPUT_NAME bncsutil)

if(UNIX)
    set_target_properties(bncsutil PROPERTIES VERSION "${VERSION_MAJOR}.${VERSION_MINOR}.${VERSION_PATCH}")
    set_target_properties(bncsutil PROPERTIES SOVERSION 1)

    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -O3 -Wno-multichar -fPIC")
    set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wall -O3 -Wno-multichar -fPIC")
endif()

if (WIN32)
	add_definitions(-D_CRT_SECURE_NO_WARNINGS -DMUTIL_LIB_BUILD)
endif()

if (MSVC)
	set_property(DIRECTORY PROPERTY VS_STARTUP_PROJECT "bncsutil")
endif()

install(TARGETS bncsutil RUNTIME DESTINATION bin LIBRARY DESTINATION lib ARCHIVE DESTINATION lib)
install(FILES ${HEADERS} DESTINATION include/bncsutil)

#CPack configurtion
SET(CPACK_GENERATOR "DEB" "RPM")
SET(CPACK_PACKAGE_NAME "bncsutil")
SET(CPACK_PACKAGE_DESCRIPTION_SUMMARY "Battle.Net Chat Service Utility")
SET(CPACK_PACKAGE_VENDOR "bncsutil")
SET(CPACK_PACKAGE_DESCRIPTION "\
This will install the library to /usr/local/lib and header files to /usr/local/include.\n \
Make sure these directories are in your library and include paths. \
")
SET(CPACK_RESOURCE_FILE_LICENSE "${CMAKE_CURRENT_SOURCE_DIR}/COPYING")
SET(CPACK_PACKAGE_VERSION_MAJOR "${VERSION_MAJOR}")
SET(CPACK_PACKAGE_VERSION_MINOR "${VERSION_MINOR}")
SET(CPACK_PACKAGE_VERSION_PATCH "${VERSION_PATCH}")
set(CPACK_PACKAGING_INSTALL_PREFIX "/usr/local")

#DEB configuration
SET(CPACK_DEBIAN_PACKAGE_SECTION "libs")
SET(CPACK_DEBIAN_PACKAGE_HOMEPAGE "https://github.com/BNETDocs/bncsutil")
SET(CPACK_DEBIAN_PACKAGE_MAINTAINER "imbacen@gmail.com")
SET(CPACK_DEBIAN_PACKAGE_ARCHITECTURE ${ARCH_DEB})
SET(CPACK_DEBIAN_PACKAGE_DEPENDS "libgmp10")

#RPM configuration
SET(CPACK_RPM_PACKAGE_RELEASE 1)
SET(CPACK_RPM_PACKAGE_LICENSE "${CMAKE_CURRENT_SOURCE_DIR}/COPYING")
SET(CPACK_RPM_PACKAGE_GROUP "bncsutil")
SET(CPACK_RPM_PACKAGE_URL "https://github.com/BNETDocs/bncsutil")
SET(CPACK_RPM_PACKAGE_REQUIRES "gmp")
SET(CPACK_RPM_PACKAGE_ARCHITECTURE ${ARCH_RPM})

INCLUDE(CPack)
