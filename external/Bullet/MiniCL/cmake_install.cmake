# Install script for directory: /Users/Sidorenko/Downloads/bullet-2.80-rev2531/src/MiniCL

# Set the install prefix
IF(NOT DEFINED CMAKE_INSTALL_PREFIX)
  SET(CMAKE_INSTALL_PREFIX "/Library/Frameworks")
ENDIF(NOT DEFINED CMAKE_INSTALL_PREFIX)
STRING(REGEX REPLACE "/$" "" CMAKE_INSTALL_PREFIX "${CMAKE_INSTALL_PREFIX}")

# Set the install configuration name.
IF(NOT DEFINED CMAKE_INSTALL_CONFIG_NAME)
  IF(BUILD_TYPE)
    STRING(REGEX REPLACE "^[^A-Za-z0-9_]+" ""
           CMAKE_INSTALL_CONFIG_NAME "${BUILD_TYPE}")
  ELSE(BUILD_TYPE)
    SET(CMAKE_INSTALL_CONFIG_NAME "RelWithDebInfo")
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

IF(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")
  FILE(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/." TYPE DIRECTORY FILES "/Users/Sidorenko/Downloads/bullet-2.80-rev2531/src/MiniCL/MiniCL.framework" USE_SOURCE_PERMISSIONS)
  IF(EXISTS "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/./MiniCL.framework/Versions/2.80/MiniCL" AND
     NOT IS_SYMLINK "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/./MiniCL.framework/Versions/2.80/MiniCL")
    EXECUTE_PROCESS(COMMAND "/usr/bin/install_name_tool"
      -id "/Library/Frameworks/MiniCL.framework/Versions/2.80/MiniCL"
      -change "/Users/Sidorenko/Downloads/bullet-2.80-rev2531/src/BulletCollision/BulletCollision.framework/Versions/2.80/BulletCollision" "/Library/Frameworks/BulletCollision.framework/Versions/2.80/BulletCollision"
      -change "/Users/Sidorenko/Downloads/bullet-2.80-rev2531/src/BulletDynamics/BulletDynamics.framework/Versions/2.80/BulletDynamics" "/Library/Frameworks/BulletDynamics.framework/Versions/2.80/BulletDynamics"
      -change "/Users/Sidorenko/Downloads/bullet-2.80-rev2531/src/BulletMultiThreaded/BulletMultiThreaded.framework/Versions/2.80/BulletMultiThreaded" "/Library/Frameworks/BulletMultiThreaded.framework/Versions/2.80/BulletMultiThreaded"
      -change "/Users/Sidorenko/Downloads/bullet-2.80-rev2531/src/LinearMath/LinearMath.framework/Versions/2.80/LinearMath" "/Library/Frameworks/LinearMath.framework/Versions/2.80/LinearMath"
      "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/./MiniCL.framework/Versions/2.80/MiniCL")
    IF(CMAKE_INSTALL_DO_STRIP)
      EXECUTE_PROCESS(COMMAND "/usr/bin/strip" "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/./MiniCL.framework/Versions/2.80/MiniCL")
    ENDIF(CMAKE_INSTALL_DO_STRIP)
  ENDIF()
ENDIF(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")

