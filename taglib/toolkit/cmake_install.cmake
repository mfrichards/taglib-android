# Install script for directory: /home/spmfr/work/taglib-1.7/taglib/toolkit

# Set the install prefix
IF(NOT DEFINED CMAKE_INSTALL_PREFIX)
  SET(CMAKE_INSTALL_PREFIX "/home/spmfr/android/android-ndk-r6b/toolchains/arm-linux-androideabi-4.4.3/prebuilt/linux-x86/user")
ENDIF(NOT DEFINED CMAKE_INSTALL_PREFIX)
STRING(REGEX REPLACE "/$" "" CMAKE_INSTALL_PREFIX "${CMAKE_INSTALL_PREFIX}")

# Set the install configuration name.
IF(NOT DEFINED CMAKE_INSTALL_CONFIG_NAME)
  IF(BUILD_TYPE)
    STRING(REGEX REPLACE "^[^A-Za-z0-9_]+" ""
           CMAKE_INSTALL_CONFIG_NAME "${BUILD_TYPE}")
  ELSE(BUILD_TYPE)
    SET(CMAKE_INSTALL_CONFIG_NAME "Release")
  ENDIF(BUILD_TYPE)
  MESSAGE(STATUS "Install configuration: \"${CMAKE_INSTALL_CONFIG_NAME}\"")
ENDIF(NOT DEFINED CMAKE_INSTALL_CONFIG_NAME)

# Set the component getting installed.
IF(NOT CMAKE_INSTALL_COMPONENT)
  IF(COMPONENT)
    MESSAGE(STATUS "Install component: \"${COMPONENT}\"")
    SET(CMAKE_INSTALL_COMPONENT "${COMPONENT}")
  ELSE(COMPONENT)
    SET(CMAKE_INSTALL_COMPONENT)
  ENDIF(COMPONENT)
ENDIF(NOT CMAKE_INSTALL_COMPONENT)

# Install shared libraries without execute permission?
IF(NOT DEFINED CMAKE_INSTALL_SO_NO_EXE)
  SET(CMAKE_INSTALL_SO_NO_EXE "1")
ENDIF(NOT DEFINED CMAKE_INSTALL_SO_NO_EXE)

IF(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")
  FILE(INSTALL DESTINATION "/home/spmfr/android/android-ndk-r6b/toolchains/arm-linux-androideabi-4.4.3/prebuilt/linux-x86/user/include/taglib" TYPE FILE FILES
    "/home/spmfr/work/taglib-1.7/taglib/toolkit/taglib.h"
    "/home/spmfr/work/taglib-1.7/taglib/toolkit/tstring.h"
    "/home/spmfr/work/taglib-1.7/taglib/toolkit/tlist.h"
    "/home/spmfr/work/taglib-1.7/taglib/toolkit/tlist.tcc"
    "/home/spmfr/work/taglib-1.7/taglib/toolkit/tstringlist.h"
    "/home/spmfr/work/taglib-1.7/taglib/toolkit/tbytevector.h"
    "/home/spmfr/work/taglib-1.7/taglib/toolkit/tbytevectorlist.h"
    "/home/spmfr/work/taglib-1.7/taglib/toolkit/tfile.h"
    "/home/spmfr/work/taglib-1.7/taglib/toolkit/tmap.h"
    "/home/spmfr/work/taglib-1.7/taglib/toolkit/tmap.tcc"
    )
ENDIF(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")

