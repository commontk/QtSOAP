

SET(KIT_SRCS
  qtsoap.cpp
  qtsoap.h
  )

SET(KIT_MOC_SRCS
  qtsoap.h
  )
  
INCLUDE_DIRECTORIES(
  ${CMAKE_CURRENT_SOURCE_DIR}
  ${CMAKE_CURRENT_BINARY_DIR}
  )

if(QtSOAP_QT_VERSION VERSION_LESS "5")
  QT4_WRAP_CPP(KIT_MOC_CPP ${KIT_MOC_SRCS})
else()
  qt5_wrap_cpp(KIT_MOC_CPP ${KIT_MOC_SRCS})
endif()

SET(libname ${PROJECT_NAME})
ADD_LIBRARY(${libname} SHARED
  ${KIT_SRCS}
  ${KIT_MOC_CPP}
  )

if(QtSOAP_QT_VERSION VERSION_LESS "5")
  set(${PROJECT_NAME}_LINK_LIBRARIES ${QT_LIBRARIES})
else()
  set(${PROJECT_NAME}_LINK_LIBRARIES Qt5::Xml Qt5::Network)
endif()

TARGET_LINK_LIBRARIES(
  ${libname}
  ${${PROJECT_NAME}_LINK_LIBRARIES}
  )

#-----------------------------------------------------------------------------
#
# To fix compilation problem: relocation R_X86_64_32 against `a local symbol' can not be
# used when making a shared object; recompile with -fPIC
#
IF( CMAKE_SYSTEM_PROCESSOR STREQUAL "x86_64" )
  SET_TARGET_PROPERTIES(${PROJECT_NAME} PROPERTIES COMPILE_FLAGS "-fPIC")
ENDIF( CMAKE_SYSTEM_PROCESSOR STREQUAL "x86_64" )
