PROJECT(globalplatform C)
CMAKE_MINIMUM_REQUIRED(VERSION 2.8)
SET(VERSION "6.1.0")

SET(CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR}/cmake_modules/)

IF(UNIX)
    # Create PkgConfig file
    CONFIGURE_FILE(${CMAKE_CURRENT_SOURCE_DIR}/globalplatform.pc.in ${CMAKE_CURRENT_BINARY_DIR}/globalplatform.pc @ONLY)
    INSTALL(FILES ${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}.pc DESTINATION lib${LIB_SUFFIX}/pkgconfig)
ENDIF(UNIX)

set(DOXYFILE_SOURCE_DIR ${PROJECT_SOURCE_DIR}/src)
set(DOXYFILE_LATEX OFF)
include(UseDoxygen)

ADD_SUBDIRECTORY(src)
