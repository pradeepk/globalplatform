##
# Copyright (c) 2010 Daniel Pfeifer <daniel@pfeifer-mail.de>
# Copyright (c) 2011 Karsten Ohme <k_o_@users.sourceforge.net>
#
# CPACK_DEBIAN_PACKAGE_NAME - used as "Source" in control file, default TOLOWER "${CPACK_PACKAGE_NAME}"
# CPACK_DEBIAN_PACKAGE_PRIORITY - used as "Priority" in control file, default "optional"
# CPACK_DEBIAN_PACKAGE_SECTION - used as "Section" in control file, default "devel"
# CPACK_DEBIAN_PACKAGE_HOMEPAGE - used in "Homepage" field in control file
# CPACK_DEBIAN_BUILD_DEPENDS - use in "Build-Depends" field in control file, cmake is automatically added
# CPACK_DEBIAN_PACKAGE_DEPENDS - used as "Depends" field in the control file, default "${shlibs:Depends}, ${misc:Depends}" and "${CPACK_PACKAGE_NAME} (= ${binary:Version}) " 
# for components. Instead of "binary:Version" "Source-Version" is used under CPACK_DEBIAN_PACKAGE_DISTRIBUTION is "dapper"  
# 
# CPACK_PACKAGE_DESCRIPTION_FILE - used main text in "Description" field of control file
# CPACK_DEBIAN_PACKAGE_UPSTREAM_AUTHOR - used as upstream author in copyright file (format: Name <email>), default ${CPACK_PACKAGE_CONTACT}
# CPACK_DEBIAN_PACKAGE_UPSTREAM_AUTHOR_NAME - used as upstream author name in copyright file, default ${CPACK_PACKAGE_VENDOR}  
# CPACK_DEBIAN_PACKAGE_UPSTREAM_COPYRIGHT_YEAR - used as the copyright year in copyright file, default this year
# CPACK_DEBIAN_PACKAGE_UPSTREAM_URL - used as upstream url in copyright file, default CPACK_DEBIAN_PACKAGE_HOMEPAGE
# CPACK_DEBIAN_PACKAGE_LICENSE - used as license indicator for the copyright file generation, possible values gpl, lgpl, bsd, apache
# CPACK_DEBIAN_PACKAGE_DISTRIBUTION - distribution name, default "maverick"
#
# CPACK_DEBIAN_PACKAGE_RECOMMENDS - used as "Recommends" field in control file
# CPACK_DEBIAN_PACKAGE_SUGGESTS - used as "Suggests" field in control file
# CPACK_DEBIAN_PACKAGE_PREDEPENDS - used as "Pre-Depends" field in control file
# CPACK_DEBIAN_PACKAGE_BREAKS - used as "Breaks" field in control file
# CPACK_DEBIAN_PACKAGE_CONFLICTS - used as "Conflicts" field in control file
# CPACK_DEBIAN_PACKAGE_REPLACES - used as "Replaces" field in control file
# CPACK_DEBIAN_PACKAGE_ENHANCES - used as "Enhances" field in control file
#
#
#
# CPACK_COMPONENTS_ALL - list of additional components - used for the "Package" field in the control file for additional components of a package, e.g. for development files for a library this would be "dev"
# CPACK_COMPONENT_${COMPONENT}_DISPLAY_NAME - used as additional short description for the "Description" field of additional packages. ${COMPONENT} must be in the list of CPACK_COMPONENTS_ALL, e.g. DEV
# CPACK_COMPONENT_${COMPONENT}_DESCRIPTION - used as additional description for the "Description" field of additional packages. ${COMPONENT} must be in the list of CPACK_COMPONENTS_ALL, e.g. DEV
# CPACK_COMPONENT_${COMPONENT}_DEPENDS - used for the "Depends" field of additional packages. ${COMPONENT} must be in the list of CPACK_COMPONENTS_ALL, e.g. DEV
# CPACK_COMPONENT_${COMPONENT}_SECTION - used for the "Section" field of additional packages. ${COMPONENT} must be in the list of CPACK_COMPONENTS_ALL, e.g. DEV
#
# CPACK_PACKAGE_CONTACT - used as "Maintainer" field in control and copyright file
# CPACK_PACKAGE_VENDOR - used as "Homepage" in control file
# CPACK_PACKAGE_DESCRIPTION_SUMMARY - used as first line of all "Description" fields for all packages in control file
#
# DPUT_HOST - used as host for dput for uploading the file to Launchpad
# CPACK_DEBIAN_PACKAGE_TYPE - used for determining the build type, "snapshot" or "release" is possible, default snapshot
#
# The format of the resulting versioning scheme is the following: ${CPACK_DEBIAN_PACKAGE_NAME}-${CPACK_PACKAGE_VERSION}-<BUILD_NUMBER_PREFIX><BUILD_NUMBER>[-SNAPSHOT-<DATE>]~${CPACK_DEBIAN_PACKAGE_DISTRIBUTION}
# e.g. libfoo1-1.2.0-0ubuntu12011-04-02-03-17-38+0200~maverick 
# "0ubuntu" stands for the first package in Ubuntu when there is no Debian package existing, the "04-01 21:00:33+02:00" specifies the creation date of this snapshot version, "maverick" is the used Ubuntu version
# The [-SNAPSHOT-<DATE>] part is only used when building snapshots to assert unique upgradable versions.
# CPACK_DEBIAN_PACKAGE_BUILD_NUMBER_PREFIX - used as a prefix for the build number, default ""
# CPACK_DEBIAN_PACKAGE_BUILD_NUMBER - used for the build number
# CPACK_DEBIAN_NATIVE_PACKAGE - if set a native package is build, default not set
#
#
##

find_program(DEBUILD_EXECUTABLE debuild)
find_program(DPUT_EXECUTABLE dput)

if(NOT DEBUILD_EXECUTABLE OR NOT DPUT_EXECUTABLE)
  MESSAGE(WARNING "${DEBUILD_EXECUTABLE} or ${DPUT_EXECUTABLE} not installed.")
  return()
endif(NOT DEBUILD_EXECUTABLE OR NOT DPUT_EXECUTABLE)

# DEBIAN/control
# debian policy enforce lower case for package name
# Package: (mandatory)
IF(NOT CPACK_DEBIAN_PACKAGE_NAME)
  STRING(TOLOWER "${CPACK_PACKAGE_NAME}" CPACK_DEBIAN_PACKAGE_NAME)
ENDIF(NOT CPACK_DEBIAN_PACKAGE_NAME)

# Section: (recommended)
IF(NOT CPACK_DEBIAN_PACKAGE_SECTION)
  SET(CPACK_DEBIAN_PACKAGE_SECTION "devel")
ENDIF(NOT CPACK_DEBIAN_PACKAGE_SECTION)

# Priority: (recommended)
IF(NOT CPACK_DEBIAN_PACKAGE_PRIORITY)
  SET(CPACK_DEBIAN_PACKAGE_PRIORITY "optional")
ENDIF(NOT CPACK_DEBIAN_PACKAGE_PRIORITY)

# Section: 
set(CPACK_DEBIAN_PACKAGE_DEPENDS "\${shlibs:Depends}, \${misc:Depends}")

# Description:  
file(STRINGS ${CPACK_PACKAGE_DESCRIPTION_FILE} DESC_LINES)
foreach(LINE ${DESC_LINES})
  set(DEB_LONG_DESCRIPTION "${DEB_LONG_DESCRIPTION} ${LINE}\n")
endforeach(LINE ${DESC_LINES})

file(REMOVE_RECURSE ${CMAKE_BINARY_DIR}/Debian)
set(DEBIAN_SOURCE_DIR ${CMAKE_BINARY_DIR}/Debian/${CPACK_DEBIAN_PACKAGE_NAME}-${CPACK_PACKAGE_VERSION}-source)
execute_process(COMMAND ${CMAKE_COMMAND} -E
  copy_directory ${CMAKE_SOURCE_DIR} ${DEBIAN_SOURCE_DIR}
  )
execute_process(COMMAND ${CMAKE_COMMAND} -E
  remove_directory ${DEBIAN_SOURCE_DIR}/.git
  )

file(MAKE_DIRECTORY ${DEBIAN_SOURCE_DIR}/debian)

##############################################################################
# debian/control
set(DEBIAN_CONTROL ${DEBIAN_SOURCE_DIR}/debian/control)
file(WRITE ${DEBIAN_CONTROL}
  "Source: ${CPACK_DEBIAN_PACKAGE_NAME}\n"
  "Section: ${CPACK_DEBIAN_PACKAGE_SECTION}\n"
  "Priority: ${CPACK_DEBIAN_PACKAGE_PRIORITY}\n"
  "Maintainer: ${CPACK_PACKAGE_CONTACT}\n"
  "Build-Depends: "
  )

foreach(DEP ${CPACK_DEBIAN_BUILD_DEPENDS})
  file(APPEND ${DEBIAN_CONTROL} "${DEP}, ")
endforeach(DEP ${CPACK_DEBIAN_BUILD_DEPENDS})  

file(APPEND ${DEBIAN_CONTROL} "cmake\n"
  "Standards-Version: 3.8.4\n"
  "Homepage: ${CPACK_DEBIAN_PACKAGE_HOMEPAGE}\n"
  "\n"
  "Package: ${CPACK_DEBIAN_PACKAGE_NAME}\n"
  "Architecture: any\n"
  "Depends: ${CPACK_DEBIAN_PACKAGE_DEPENDS}\n"
  )

# Recommends:  
IF(CPACK_DEBIAN_PACKAGE_RECOMMENDS)
file(APPEND ${DEBIAN_CONTROL}
  "Recommends: ${CPACK_DEBIAN_PACKAGE_RECOMMENDS}\n"
  )
ENDIF(CPACK_DEBIAN_PACKAGE_RECOMMENDS)

# Suggests
IF(CPACK_DEBIAN_PACKAGE_SUGGESTS)
  file(APPEND ${DEBIAN_CONTROL}
    "Suggests: ${CPACK_DEBIAN_PACKAGE_SUGGESTS}\n"
    )
ENDIF(CPACK_DEBIAN_PACKAGE_SUGGESTS)

# Pre-Depends:
IF(CPACK_DEBIAN_PACKAGE_PREDEPENDS)
file(APPEND ${DEBIAN_CONTROL}
  "Pre-Depends: ${CPACK_DEBIAN_PACKAGE_PREDEPENDS}\n"
  )
ENDIF(CPACK_DEBIAN_PACKAGE_PREDEPENDS)

# Conflicts: 
IF(CPACK_DEBIAN_PACKAGE_CONFLICTS)
file(APPEND ${DEBIAN_CONTROL}
  "Conflicts: ${CPACK_DEBIAN_PACKAGE_CONFLICTS}\n"
  )
ENDIF(CPACK_DEBIAN_PACKAGE_CONFLICTS)

# Enhances:
IF(CPACK_DEBIAN_PACKAGE_ENHANCES)
file(APPEND ${DEBIAN_CONTROL}
  "Enhances: ${CPACK_DEBIAN_PACKAGE_ENHANCES}\n"
  )
ENDIF(CPACK_DEBIAN_PACKAGE_ENHANCES)

# Replaces:
IF(CPACK_DEBIAN_PACKAGE_REPLACES)
file(APPEND ${DEBIAN_CONTROL}
  "Replaces: ${CPACK_DEBIAN_PACKAGE_REPLACES}\n"
  )
ENDIF(CPACK_DEBIAN_PACKAGE_REPLACES)

file(APPEND ${DEBIAN_CONTROL}
  "Description: ${CPACK_PACKAGE_DESCRIPTION_SUMMARY}\n"
  "${DEB_LONG_DESCRIPTION}"
  )
  
foreach(COMPONENT ${CPACK_COMPONENTS_ALL})
  string(TOUPPER ${COMPONENT} UPPER_COMPONENT)
  set(DEPENDS "${CPACK_DEBIAN_PACKAGE_NAME}")
  IF(CPACK_DEBIAN_PACKAGE_DISTRIBUTION STREQUAL "dapper")
    set(DEPENDS "${DEPENDS} (= \${Source-Version})")
  ELSE(CPACK_DEBIAN_PACKAGE_DISTRIBUTION STREQUAL "dapper")
    set(DEPENDS "${DEPENDS} (= \${binary:Version})")
  ENDIF(CPACK_DEBIAN_PACKAGE_DISTRIBUTION STREQUAL "dapper")   
  foreach(DEP ${CPACK_COMPONENT_${UPPER_COMPONENT}_DEPENDS})
      set(DEPENDS "${DEPENDS}, ${CPACK_DEBIAN_PACKAGE_NAME}-${DEP}")
  endforeach(DEP ${CPACK_COMPONENT_${UPPER_COMPONENT}_DEPENDS})
  file(APPEND ${DEBIAN_CONTROL} "\n"
    "Package: ${CPACK_DEBIAN_PACKAGE_NAME}-${COMPONENT}\n"
    "Section: ${CPACK_COMPONENT_${UPPER_COMPONENT}_SECTION}\n"
    "Architecture: any\n"
    "Depends: ${DEPENDS}\n"
    "Description: ${CPACK_PACKAGE_DESCRIPTION_SUMMARY}"
    ": ${CPACK_COMPONENT_${UPPER_COMPONENT}_DISPLAY_NAME}\n"
    "${DEB_LONG_DESCRIPTION}"
    " .\n"
    " ${CPACK_COMPONENT_${UPPER_COMPONENT}_DESCRIPTION}\n"
    )
endforeach(COMPONENT ${CPACK_COMPONENTS_ALL})

##############################################################################
# debian/copyright
set(DEBIAN_COPYRIGHT ${DEBIAN_SOURCE_DIR}/debian/copyright)

IF(NOT CPACK_DEBIAN_PACKAGE_LICENSE)
  set(CPACK_DEBIAN_PACKAGE_LICENSE gpl)
ENDIF(NOT CPACK_DEBIAN_PACKAGE_LICENSE)

IF(NOT CPACK_DEBIAN_PACKAGE_UPSTREAM_AUTHOR)
  set(CPACK_DEBIAN_PACKAGE_UPSTREAM_AUTHOR ${CPACK_PACKAGE_CONTACT})
ENDIF(NOT CPACK_DEBIAN_PACKAGE_UPSTREAM_AUTHOR)

IF(NOT CPACK_DEBIAN_PACKAGE_UPSTREAM_AUTHOR_NAME)
  set(CPACK_DEBIAN_PACKAGE_UPSTREAM_AUTHOR_NAME ${CPACK_PACKAGE_VENDOR})
ENDIF(NOT CPACK_DEBIAN_PACKAGE_UPSTREAM_AUTHOR_NAME)

IF(NOT CPACK_DEBIAN_PACKAGE_UPSTREAM_URL)
  set(CPACK_DEBIAN_PACKAGE_UPSTREAM_URL ${CPACK_DEBIAN_PACKAGE_HOMEPAGE})
ENDIF(NOT CPACK_DEBIAN_PACKAGE_UPSTREAM_URL) 

IF(NOT CPACK_DEBIAN_PACKAGE_UPSTREAM_COPYRIGHT_YEAR)
  execute_process(COMMAND date +%Y OUTPUT_VARIABLE CPACK_DEBIAN_PACKAGE_UPSTREAM_COPYRIGHT_YEAR)
  STRING(REPLACE "\n" "" CPACK_DEBIAN_PACKAGE_UPSTREAM_COPYRIGHT_YEAR ${CPACK_DEBIAN_PACKAGE_UPSTREAM_COPYRIGHT_YEAR})
ENDIF(NOT CPACK_DEBIAN_PACKAGE_UPSTREAM_COPYRIGHT_YEAR) 

execute_process(COMMAND date +%Y OUTPUT_VARIABLE CPACK_DEBIAN_PACKAGE_YEAR)
STRING(REPLACE "\n" "" CPACK_DEBIAN_PACKAGE_YEAR ${CPACK_DEBIAN_PACKAGE_YEAR})

execute_process(COMMAND date -R OUTPUT_VARIABLE CPACK_DEBIAN_PACKAGE_DATE)
STRING(REPLACE "\n" "" CPACK_DEBIAN_PACKAGE_DATE ${CPACK_DEBIAN_PACKAGE_DATE})

set(POSSIBLE_LICENSES gpl lgpl bsd apache)
list(FIND POSSIBLE_LICENSES ${CPACK_DEBIAN_PACKAGE_LICENSE} CPACK_DEBIAN_PACKAGE_LICENSE_FOUND)

IF(CPACK_DEBIAN_PACKAGE_LICENSE_FOUND EQUAL "-1")
  message(FATAL_ERROR "License ${CPACK_DEBIAN_PACKAGE_LICENSE} is unknown.")
ENDIF(CPACK_DEBIAN_PACKAGE_LICENSE_FOUND EQUAL "-1")

find_path(COPYRIGHT_FILES_DIRECTORY copyright.${CPACK_DEBIAN_PACKAGE_LICENSE} PATHS ${CMAKE_MODULE_PATH})
execute_process(COMMAND ${CMAKE_COMMAND} -E
  copy ${COPYRIGHT_FILES_DIRECTORY}/copyright.${CPACK_DEBIAN_PACKAGE_LICENSE} ${DEBIAN_COPYRIGHT}
  )

# Here also CONFIGURE_FILE might be better
FILE(READ ${DEBIAN_COPYRIGHT} COPYRIGHT_TEMP)
STRING(REPLACE "<Maintainer>" ${CPACK_PACKAGE_CONTACT} COPYRIGHT_TEMP ${COPYRIGHT_TEMP})
STRING(REPLACE "<Date>" ${CPACK_DEBIAN_PACKAGE_DATE} COPYRIGHT_TEMP ${COPYRIGHT_TEMP})
STRING(REPLACE "<Year>" ${CPACK_DEBIAN_PACKAGE_YEAR} COPYRIGHT_TEMP ${COPYRIGHT_TEMP})
STRING(REPLACE "<UpstreamURL>" ${CPACK_DEBIAN_PACKAGE_UPSTREAM_URL} COPYRIGHT_TEMP ${COPYRIGHT_TEMP})
STRING(REPLACE "<UpstreamAuthor>" ${CPACK_DEBIAN_PACKAGE_UPSTREAM_AUTHOR} COPYRIGHT_TEMP ${COPYRIGHT_TEMP})
STRING(REPLACE "<YearUpstreamCopyright>" ${CPACK_DEBIAN_PACKAGE_UPSTREAM_COPYRIGHT_YEAR} COPYRIGHT_TEMP ${COPYRIGHT_TEMP})
STRING(REPLACE "<UpstreamAuthorName>" ${CPACK_DEBIAN_PACKAGE_UPSTREAM_AUTHOR_NAME} COPYRIGHT_TEMP ${COPYRIGHT_TEMP})     
FILE(WRITE ${DEBIAN_COPYRIGHT} ${COPYRIGHT_TEMP})

##############################################################################
# debian/rules
set(DEBIAN_RULES ${DEBIAN_SOURCE_DIR}/debian/rules)
file(WRITE ${DEBIAN_RULES}
  "#!/usr/bin/make -f\n"
  "\n"
  "BUILDDIR = build_dir\n"
  "\n"
  "build:\n"
  "	mkdir $(BUILDDIR)\n"
  "	cd $(BUILDDIR); cmake ..\n"
  "	make -C $(BUILDDIR) preinstall\n"
  "	touch build\n"
  "\n"
  "binary: binary-indep binary-arch\n"
  "\n"
  "binary-indep: build\n"
  "\n"
  "binary-arch: build\n"
  "	cd $(BUILDDIR); cmake -DCOMPONENT=Unspecified -DCMAKE_INSTALL_PREFIX=../debian/tmp/usr -P cmake_install.cmake\n"
  "	mkdir debian/tmp/DEBIAN\n"
  "	dpkg-gencontrol -p${CPACK_DEBIAN_PACKAGE_NAME}\n"
  "	dpkg --build debian/tmp ..\n"
  )

foreach(COMPONENT ${CPACK_COMPONENTS_ALL})
  set(PATH debian/tmp_${COMPONENT})
  set(PACKAGE ${CPACK_DEBIAN_PACKAGE_NAME}-${COMPONENT})
  file(APPEND ${DEBIAN_RULES}
    "	cd $(BUILDDIR); cmake -DCOMPONENT=${COMPONENT} -DCMAKE_INSTALL_PREFIX=../${PATH}/usr -P cmake_install.cmake\n"
    "	mkdir ${PATH}/DEBIAN\n"
    "	dpkg-gencontrol -p${PACKAGE} -P${PATH}\n"
    "	dpkg --build ${PATH} ..\n"
    )
endforeach(COMPONENT ${CPACK_COMPONENTS_ALL})

file(APPEND ${DEBIAN_RULES}
  "\n"
  "clean:\n"
  "	rm -f build\n"
  "	rm -rf $(BUILDDIR)\n"
  "\n"
  ".PHONY: binary binary-arch binary-indep clean\n"
  )

execute_process(COMMAND chmod +x ${DEBIAN_RULES})

##############################################################################
# debian/compat - 5 is used to also support dapper
file(WRITE ${DEBIAN_SOURCE_DIR}/debian/compat "5")

##############################################################################
# debian/source/format
IF(CPACK_DEBIAN_NATIVE_PACKAGE)
  file(WRITE ${DEBIAN_SOURCE_DIR}/debian/source/format "3.0 (native)")
ELSE(CPACK_DEBIAN_NATIVE_PACKAGE)
  file(WRITE ${DEBIAN_SOURCE_DIR}/debian/source/format "3.0 (quilt)")
ENDIF(CPACK_DEBIAN_NATIVE_PACKAGE)

##############################################################################
# debian/changelog

IF(NOT CPACK_DEBIAN_PACKAGE_DISTRIBUTION)
  set(CPACK_DEBIAN_PACKAGE_DISTRIBUTION "maverick")
ENDIF(NOT CPACK_DEBIAN_PACKAGE_DISTRIBUTION)

IF(NOT CPACK_DEBIAN_PACKAGE_TYPE)
  set(CPACK_DEBIAN_PACKAGE_TYPE "snapshot")
ENDIF(NOT CPACK_DEBIAN_PACKAGE_TYPE)

set(DEBIAN_CHANGELOG ${DEBIAN_SOURCE_DIR}/debian/changelog)
execute_process(COMMAND date -R  OUTPUT_VARIABLE DATE_TIME)


IF(CPACK_DEBIAN_PACKAGE_TYPE STREQUAL "snapshot")
  execute_process(COMMAND date +%F-%0k-%0M-%0S%z OUTPUT_VARIABLE SNAPSHOT_DATE_TIME)
  set(CPACK_DEBIAN_PACKAGE_BUILD_NUMBER "${CPACK_DEBIAN_PACKAGE_BUILD_NUMBER}-SNAPSHOT-${SNAPSHOT_DATE_TIME}")
  STRING(REPLACE "\n" "" CPACK_DEBIAN_PACKAGE_BUILD_NUMBER ${CPACK_DEBIAN_PACKAGE_BUILD_NUMBER})
ENDIF(CPACK_DEBIAN_PACKAGE_TYPE STREQUAL "snapshot")

file(WRITE ${DEBIAN_CHANGELOG}
  "${CPACK_DEBIAN_PACKAGE_NAME} (${CPACK_PACKAGE_VERSION}-${CPACK_DEBIAN_PACKAGE_BUILD_NUMBER_PREFIX}${CPACK_DEBIAN_PACKAGE_BUILD_NUMBER}~${CPACK_DEBIAN_PACKAGE_DISTRIBUTION}) ${CPACK_DEBIAN_PACKAGE_DISTRIBUTION}; urgency=low\n\n"
  "  * Package built with CMake\n\n"
  " -- ${CPACK_PACKAGE_CONTACT}  ${DATE_TIME}"
  )


##############################################################################
# debuild -S
set(DEB_SOURCE_CHANGES
  ${CPACK_DEBIAN_PACKAGE_NAME}_${CPACK_PACKAGE_VERSION}_source.changes
  )

add_custom_command(OUTPUT ${CMAKE_BINARY_DIR}/Debian/${DEB_SOURCE_CHANGES}
  COMMAND ${CMAKE_COMMAND} package-source
  COMMAND ${CMAKE_COMMAND} -E copy ${CMAKE_BINARY_DIR}/${CPACK_SOURCE_PACKAGE_FILE_NAME}.${CPACK_SOURCE_GENERATOR} ${CMAKE_BINARY_DIR}/Debian/${CPACK_DEBIAN_PACKAGE_NAME}-${CPACK_PACKAGE_VERSION}.orig.${CPACK_SOURCE_GENERATOR}
  COMMAND ${DEBUILD_EXECUTABLE} -S
  WORKING_DIRECTORY ${DEBIAN_SOURCE_DIR}
  )

add_custom_target(package-ubuntu 
  DEPENDS ${CMAKE_BINARY_DIR}/Debian/${DEB_SOURCE_CHANGES}
  WORKING_DIRECTORY ${CMAKE_BINARY_DIR}/Debian
  )
#add_custom_target(package-ubuntu ${DEBUILD_EXECUTABLE} -S
#  WORKING_DIRECTORY ${DEBIAN_SOURCE_DIR}
#  )

##############################################################################
# dput ppa:your-lp-id/ppa <source.changes>
add_custom_target(dput ${DPUT_EXECUTABLE} ${DPUT_HOST} ${DEB_SOURCE_CHANGES}
  DEPENDS ${CMAKE_BINARY_DIR}/Debian/${DEB_SOURCE_CHANGES}
  WORKING_DIRECTORY ${CMAKE_BINARY_DIR}/Debian
  )

# Also clean Debian directory
set_directory_properties(PROPERTIES ADDITIONAL_MAKE_CLEAN_FILES ${DEBIAN_SOURCE_DIR})