

set(KIT_SRCS
  qtsoap.cpp
  qtsoap.h
  )

set(KIT_MOC_SRCS
  qtsoap.h
  )

include_directories(
  ${CMAKE_CURRENT_SOURCE_DIR}
  ${CMAKE_CURRENT_BINARY_DIR}
  )

if(QtSOAP_QT_VERSION VERSION_LESS "5")
  QT4_WRAP_CPP(KIT_MOC_CPP ${KIT_MOC_SRCS})
else()
  qt5_wrap_cpp(KIT_MOC_CPP ${KIT_MOC_SRCS})
endif()

set(libname ${PROJECT_NAME})
add_library(${libname} SHARED
  ${KIT_SRCS}
  ${KIT_MOC_CPP}
  )

if(QtSOAP_QT_VERSION VERSION_LESS "5")
  set(${PROJECT_NAME}_LINK_LIBRARIES ${QT_LIBRARIES})
else()
  set(${PROJECT_NAME}_LINK_LIBRARIES Qt5::Xml Qt5::Network)
endif()

target_link_libraries(
  ${libname}
  ${${PROJECT_NAME}_LINK_LIBRARIES}
  )

#-----------------------------------------------------------------------------
#
# To fix compilation problem: relocation R_X86_64_32 against `a local symbol' can not be
# used when making a shared object; recompile with -fPIC
#
if( CMAKE_SYSTEM_PROCESSOR STREQUAL "x86_64" )
  set_target_properties(${PROJECT_NAME} PROPERTIES COMPILE_FLAGS "-fPIC")
endif()
