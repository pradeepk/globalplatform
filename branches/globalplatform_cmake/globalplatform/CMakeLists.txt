PROJECT(globalplatform C)
CMAKE_MINIMUM_REQUIRED(VERSION 2.8)

SET( ${PROJECT_NAME}_CURRENT 6 )
SET( ${PROJECT_NAME}_REVISION 1 )
SET( ${PROJECT_NAME}_AGE 0 )
SET(VERSION "${${CMAKE_PROJECT_NAME}_CURRENT}.${${CMAKE_PROJECT_NAME}_REVISION}.${${CMAKE_PROJECT_NAME}_AGE}")

SET(CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR}/cmake_modules/)

IF(UNIX)
    # Create PkgConfig file
    CONFIGURE_FILE(${CMAKE_CURRENT_SOURCE_DIR}/globalplatform.pc.in ${CMAKE_CURRENT_BINARY_DIR}/globalplatform.pc @ONLY)
    INSTALL(FILES ${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}.pc DESTINATION lib${LIB_SUFFIX}/pkgconfig)
ENDIF(UNIX)

set(DOXYFILE_SOURCE_DIR ${PROJECT_SOURCE_DIR}/src)
set(DOXYFILE_LATEX OFF)
include(UseDoxygen)

INSTALL(FILES ${CMAKE_CURRENT_BINARY_DIR}/AUTHORS ${CMAKE_CURRENT_BINARY_DIR}/ChangeLog 
              ${CMAKE_CURRENT_BINARY_DIR}/COPYING ${CMAKE_CURRENT_BINARY_DIR}/COPYING.LESSER 
              ${CMAKE_CURRENT_BINARY_DIR}/NEWS ${CMAKE_CURRENT_BINARY_DIR}/README DESTINATION . )

# build a CPack driven installer package

IF(WIN32)
set(CPACK_GENERATOR "ZIP")
set(CPACK_SOURCE_GENERATOR "ZIP")
ELSE(WIN32)
set(CPACK_GENERATOR "TGZ")
set(CPACK_SOURCE_GENERATOR "TGZ")
ENDIF(WIN32)

set(CPACK_PACKAGE_DESCRIPTION_SUMMARY  "The GlobalPlatform Library is a smart card management library for providing access to OpenPlatform 2.0.1' and GlobalPlatform 2.1.1 conforming smart cards.")
set(CPACK_PACKAGE_FILE_NAME            "${CMAKE_PROJECT_NAME}-binary-${VERSION}")
set(CPACK_SOURCE_PACKAGE_FILE_NAME "${CMAKE_PROJECT_NAME}-${VERSION}")
set(CPACK_PACKAGE_INSTALL_DIRECTORY    "${CMAKE_PROJECT_NAME}-${VERSION}")
set(CPACK_PACKAGE_VENDOR               "Karsten Ohme")
set(CPACK_PACKAGE_CONTACT              "Karsten Ohme <k_o_@users.sourceforge.net>")
set(CPACK_PACKAGE_VERSION              "${VERSION}")
set(CPACK_RESOURCE_FILE_LICENSE "${CMAKE_HOME_DIRECTORY}/COPYING.LESSER")
set(CPACK_PACKAGE_VERSION_MAJOR        "${${CMAKE_PROJECT_NAME}_CURRENT}")
set(CPACK_PACKAGE_VERSION_MINOR        "${${CMAKE_PROJECT_NAME}_REVISION}")
set(CPACK_PACKAGE_VERSION_PATCH        "${${CMAKE_PROJECT_NAME}_AGE}")
set(CPACK_SOURCE_IGNORE_FILES ".*~;/\\\\.svn/;/\\\\globalplatform.lib;/\\\\globalplatform.dll;/\\\\CMakeFiles;/${CPACK_SOURCE_PACKAGE_FILE_NAME}.*;/${CPACK_PACKAGE_FILE_NAME}.*;/\\\\CPack*;/\\\\CMakeCache.txt;/\\\\cmake_install.*;/\\\\Makefile;/\\\\_CPack_Packages;/\\\\libglobalplatform.so;/\\\\libglobalplatform.a;/\\\\globalplatform.exp;/\\\\globalplatform.manifest;/\\\\install_manifest.txt;${CPACK_SOURCE_IGNORE_FILES}")

#set(CPACK_INSTALL_COMMANDS "${CMAKE_COMMAND} -E copy ${CMAKE_SOURCE_DIR}/CMakeLists.txt ${CMAKE_BINARY_DIR}/_CPack_Packages/Linux-Source/TGZ/${CPACK_SOURCE_PACKAGE_FILE_NAME}")
#set(CPACK_SOURCE_INSTALLED_DIRECTORIES "${CMAKE_SOURCE_DIR}/src")

include (CPack)

# build a Debian package for Launchpad
set(CPACK_DEBIAN_PACKAGE_NAME, "libglobalplatform6")
set(CPACK_DEBIAN_PACKAGE_PRIORITY, "extra")
set(CPACK_DEBIAN_PACKAGE_SECTION, "libs")
set(CPACK_DEBIAN_PACKAGE_HOMEPAGE, "http://globalplatform.sourceforge.net/")
set(CPACK_PACKAGE_DESCRIPTION_FILE, "${CMAKE_HOME_DIRECTORY}/description.txt")
set(CPACK_DEBIAN_PACKAGE_LICENSE, "lgpl")
set(CPACK_DEBIAN_PACKAGE_RECOMMENDS, "libgppcscconnectionplugin")
set(CPACK_DEBIAN_PACKAGE_SUGGESTS, "gpshell")
set(CPACK_COMPONENTS_ALL, "dev")
set(CPACK_COMPONENT_DEV_DISPLAY_NAME, "GlobalPlatform Library development files.")
set(CPACK_COMPONENT_DEV_DESCRIPTION, "These are the development files.")
set(CPACK_COMPONENT_DEV_SECTION, "libdevel")
set(CPACK_DEBIAN_PACKAGE_BUILD_NUMBER_PREFIX, "0ubuntu")
set(CPACK_DEBIAN_PACKAGE_BUILD_NUMBER, "1")
set(DPUT_HOST, "gpsnapshots-ppa")

# Enable usual make dist behavior
add_custom_target(dist COMMAND ${CMAKE_MAKE_PROGRAM} package_source)

ADD_SUBDIRECTORY(src)