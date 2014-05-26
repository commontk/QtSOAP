set(QtSOAP_QT_VERSION "4" CACHE STRING "Expected Qt version")
mark_as_advanced(QtSOAP_QT_VERSION)

set_property(CACHE QtSOAP_QT_VERSION PROPERTY STRINGS 4 5)

if(NOT (QtSOAP_QT_VERSION VERSION_EQUAL "4" OR QtSOAP_QT_VERSION VERSION_EQUAL "5"))
  message(FATAL_ERROR "Expected value for QtSOAP_QT_VERSION is either '4' or '5'")
endif()

if(QtSOAP_QT_VERSION VERSION_GREATER "4")
  cmake_minimum_required(VERSION 2.8.12)
  set(QT5_INSTALL_PREFIX "" CACHE PATH "The install location of Qt5")
  set(CMAKE_PREFIX_PATH ${CMAKE_PREFIX_PATH} ${QT5_INSTALL_PREFIX})
else()
  cmake_minimum_required(VERSION 2.8.2)
endif()

PROJECT(QtSOAP)

include(CTestUseLaunchers OPTIONAL)

OPTION(QtSOAP_BUILD_EXAMPLES "Build examples" OFF)

# We build QtSOAP as a static library. On Windows, this avoids copying
# a dll to the directory containing the linked executable or fiddling
# with the PATH environment variable.
# Further, if we would build QtSOAP as a shared library, each using
# library/executable must use -DQT_SOAP_IMPORT (if we don't change qtsoap.h)

#-----------------------------------------------------------------------------
# Output directories.
#
SET(output_dir ${QtSOAP_BINARY_DIR}/bin)
FOREACH(type LIBRARY RUNTIME ARCHIVE)
  IF(NOT DEFINED CMAKE_${type}_OUTPUT_DIRECTORY)
    SET(CMAKE_${type}_OUTPUT_DIRECTORY ${output_dir} CACHE INTERNAL "Single output directory for building all libraries.")
  ENDIF()
ENDFOREACH()

#-----------------------------------------------------------------------------
# Qt
#
if(QtSOAP_QT_VERSION VERSION_GREATER "4")
  find_package(Qt5 COMPONENTS Core Network Xml REQUIRED)
else()
  find_package(Qt4 4.6 COMPONENTS QtCore QtNetwork QtXml REQUIRED)
  include(${QT_USE_FILE})
endif()

#-----------------------------------------------------------------------------
# Subdirectories
#
ADD_SUBDIRECTORY(src)
IF(QtSOAP_BUILD_EXAMPLES)
  ADD_SUBDIRECTORY(examples)
ENDIF()

#-----------------------------------------------------------------------------
# Generate QtSOAPConfig file
#
CONFIGURE_FILE(UseQtSOAP.cmake.in
               ${QtSOAP_BINARY_DIR}/UseQtSOAP.cmake COPYONLY)

INCLUDE(GenerateQtSOAPConfig.cmake)
