
CMAKE_MINIMUM_REQUIRED(VERSION 2.8.2)

PROJECT(QtSOAP)

OPTION(BUILD_SHARED_LIBS "Build as shared library" ON)
OPTION(QtSOAP_BUILD_EXAMPLES "Build examples" OFF)

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
FIND_PACKAGE(Qt4 4.6 REQUIRED)
SET(QT_USE_QTNETWORK ON)
SET(QT_USE_QTXML ON)
INCLUDE(${QT_USE_FILE})

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
