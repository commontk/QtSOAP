SET(example_name easter)

SET(KIT_SRCS
  easter.cpp
  easter.h
  main.cpp
  )
  
SET(KIT_MOC_SRCS
  easter.h
  )
  
QT4_WRAP_CPP(KIT_MOC_CPP ${KIT_MOC_SRCS})
  
INCLUDE_DIRECTORIES(
  ${CMAKE_CURRENT_SOURCE_DIR}
  ${CMAKE_CURRENT_BINARY_DIR}
  )
  
ADD_EXECUTABLE(${example_name} ${KIT_SRCS} ${KIT_MOC_CPP})
TARGET_LINK_LIBRARIES(${example_name} ${PROJECT_NAME})
