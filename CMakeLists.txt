project(bncsutil)
cmake_minimum_required(VERSION 2.6)

set(SOURCE
	src/bncsutil/bsha1.cpp
	src/bncsutil/cdkeydecoder.cpp
	src/bncsutil/checkrevision.cpp
	src/bncsutil/debug.c
	src/bncsutil/decodekey.cpp
	src/bncsutil/file.cpp
	src/bncsutil/libinfo.cpp
	src/bncsutil/nls.c
	src/bncsutil/oldauth.cpp
	src/bncsutil/pe.c
	src/bncsutil/sha1.c
	src/bncsutil/stack.c	
)

set(HEADERS
	src/bncsutil/bncsutil.h
	src/bncsutil/bsha1.h
	src/bncsutil/buffer.h
	src/bncsutil/cdkeydecoder.h
	src/bncsutil/checkrevision.h
	src/bncsutil/debug.h
	src/bncsutil/decodekey.h
	src/bncsutil/file.h
	src/bncsutil/keytables.h
	src/bncsutil/libinfo.h
	src/bncsutil/ms_stdint.h
	src/bncsutil/mutil.h
	src/bncsutil/mutil_types.h
	src/bncsutil/nls.h
	src/bncsutil/oldauth.h
	src/bncsutil/pe.h
	src/bncsutil/sha1.h
	src/bncsutil/stack.h
)

set(CMAKE_MODULE_PATH CMake/Modules)

add_library(${PROJECT_NAME} SHARED ${SOURCE} ${HEADERS})
add_library(${PROJECT_NAME}_static STATIC ${SOURCE} ${HEADERS})

if (USE_MPIR)
	find_package(MPIR REQUIRED)
	include_directories(src ${MPIR_INCLUDE_DIR})
	target_link_libraries(${PROJECT_NAME} ${MPIR_LIBRARIES})
	add_definitions(-DUSE_MPIR=1)
else()
	find_package(GMP REQUIRED)
	include_directories(src ${GMP_INCLUDE_DIR})
	target_link_libraries(${PROJECT_NAME} ${GMP_LIBRARIES})
endif()

set_target_properties(${PROJECT_NAME} PROPERTIES OUTPUT_NAME bncsutil)

if(UNIX)
    set_target_properties(${PROJECT_NAME} PROPERTIES VERSION 1.3.2)
    set_target_properties(${PROJECT_NAME} PROPERTIES SOVERSION 1)
	
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -O3 -Wno-multichar -fPIC")
	set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wall -O3 -Wno-multichar -fPIC")
endif()

if (WIN32)
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -D_CRT_SECURE_NO_WARNINGS -DMUTIL_LIB_BUILD=1")
	target_link_libraries(${PROJECT_NAME} Version.lib)
endif()

SET(VERSION_MAJOR "1")
SET(VERSION_MINOR "3")
SET(VERSION_PATCH "2")

install(TARGETS bncsutil RUNTIME DESTINATION bin LIBRARY DESTINATION lib ARCHIVE DESTINATION lib)
install(FILES src/bncsutil/bncsutil.h DESTINATION include/bncsutil)

#CPack configurtion
SET(CPACK_GENERATOR "DEB" "RPM")
SET(CPACK_PACKAGE_NAME ${PROJECT_NAME})
SET(CPACK_PACKAGE_DESCRIPTION_SUMMARY "Battle.Net Chat Service Utility")
SET(CPACK_PACKAGE_VENDOR "bncsutil")
SET(CPACK_PACKAGE_DESCRIPTION_FILE "${CMAKE_CURRENT_SOURCE_DIR}/README.md")
SET(CPACK_RESOURCE_FILE_LICENSE "${CMAKE_CURRENT_SOURCE_DIR}/COPYING")
SET(CPACK_PACKAGE_VERSION_MAJOR "${VERSION_MAJOR}")
SET(CPACK_PACKAGE_VERSION_MINOR "${VERSION_MINOR}")
SET(CPACK_PACKAGE_VERSION "${VERSION_MAJOR}.${VERSION_MINOR}")

#DEB configuration
SET(CPACK_DEBIAN_PACKAGE_SECTION "libs")
SET(CPACK_DEBIAN_PACKAGE_HOMEPAGE "https://github.com/BNETDocs/bncsutil")
SET(CPACK_DEBIAN_PACKAGE_MAINTAINER "imbacen@gmail.com")
SET(CPACK_DEBIAN_PACKAGE_ARCHITECTURE "amd64")
SET(CPACK_DEBIAN_PACKAGE_DEPENDS "libgmp10")

#RPM configuration
SET(CPACK_RPM_PACKAGE_RELEASE 1)
SET(CPACK_RPM_PACKAGE_LICENSE "${CMAKE_CURRENT_SOURCE_DIR}/COPYING")
SET(CPACK_RPM_PACKAGE_GROUP "${PROJECT_NAME}")
SET(CPACK_RPM_PACKAGE_URL "https://github.com/BNETDocs/bncsutil")
SET(CPACK_RPM_PACKAGE_REQUIRES "gmp")

INCLUDE(CPack)
