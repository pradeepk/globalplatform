INCLUDE(FindPCSC)
INCLUDE(FindOpenSSL)
INCLUDE(FindZLIB)

SET(SOURCES connection.c stringify.c crypto.c loadfile.c util.c debug.c globalplatform.c)

SET(CMAKE_BUILD_TYPE "Release")

# Enable debugging output
ADD_DEFINITIONS(-DOPGP_DEBUG)

# Handle Unix build
IF(UNIX)
  SET(SOURCES ${SOURCES} dyn_unix.c)

  IF(USE_SYSTEM_MINIZIP)
    FIND_PACKAGE(PkgConfig)
    IF(PKG_CONFIG_FOUND)
      PKG_CHECK_MODULES(MINIZIP minizip)
    ENDIF(PKG_CONFIG_FOUND)
  ELSE(USE_SYSTEM_MINIZIP)
    SET(SOURCES ${SOURCES} unzip/ioapi.c unzip/unzip.c)
  ENDIF(USE_SYSTEM_MINIZIP)

  # Enable plugin loader
  ADD_DEFINITIONS(-DHAVE_DLFCN_H)
ENDIF(UNIX)

# Handle Windows build
IF(WIN32)
    SET(SOURCES ${SOURCES} dyn_win32.c unzip/unzip.c unzip/iowin32.c unzip/ioapi.c version.rc)
    ADD_DEFINITIONS(-D_CRT_SECURE_NO_WARNINGS)
    ADD_DEFINITIONS(-DUNICODE)
ENDIF(WIN32)

INCLUDE_DIRECTORIES(${PCSC_INCLUDE_DIRS} ${OPENSSL_INCLUDE_DIR} ${ZLIB_INCLUDE_DIRS})
IF(USE_SYSTEM_MINIZIP)
  INCLUDE_DIRECTORIES(${MINIZIP_INCLUDE_DIRS})
ENDIF(USE_SYSTEM_MINIZIP)

ADD_LIBRARY(globalplatform SHARED ${SOURCES})
TARGET_LINK_LIBRARIES(globalplatform ${PCSC_LIBRARIES} ${OPENSSL_LIBRARIES} ${ZLIB_LIBRARIES})
IF(USE_SYSTEM_MINIZIP)
	TARGET_LINK_LIBRARIES(globalplatform ${MINIZIP_LIBRARIES})
ENDIF(USE_SYSTEM_MINIZIP)

IF(UNIX)
  SET_TARGET_PROPERTIES(globalplatform PROPERTIES SOVERSION ${VERSION})
ENDIF(UNIX)

IF(WIN32)
  SET_TARGET_PROPERTIES(globalplatform PROPERTIES DEFINE_SYMBOL OPGP_EXPORTS)
ENDIF(WIN32)

# Install
IF(WIN32)
 INSTALL(TARGETS globalplatform RUNTIME DESTINATION lib${LIB_SUFFIX})
 INSTALL(TARGETS globalplatform ARCHIVE DESTINATION lib${LIB_SUFFIX})
ELSE(WIN32)
 INSTALL(TARGETS globalplatform LIBRARY DESTINATION lib${LIB_SUFFIX})
ENDIF(WIN32)

# Testing
IF(TESTING)
  PKG_CHECK_MODULES(CHECK check>=0.9.2)
  IF(CHECK_FOUND)
    ENABLE_TESTING()
    INCLUDE_DIRECTORIES(${CHECK_INCLUDE_DIRS})
    ADD_EXECUTABLE(globalplatformTest globalplatformTest.c)
    TARGET_LINK_LIBRARIES(globalplatformTest globalplatform ${CHECK_LIBRARIES})
    ADD_TEST(globalplatformTest ${EXECUTABLE_OUTPUT_PATH}/globalplatformTest)
    SET_TESTS_PROPERTIES(globalplatformTest PROPERTIES PASS_REGULAR_EXPRESSION "Failures: 0")
  ENDIF(CHECK_FOUND)
ENDIF(TESTING)


ADD_SUBDIRECTORY(globalplatform)