SET(example_name population)

SET(KIT_SRCS
  population.cpp
  population.h
  main.cpp
  )
  
SET(KIT_MOC_SRCS
  population.h
  )
  
QT4_WRAP_CPP(KIT_MOC_CPP ${KIT_MOC_SRCS})
  
INCLUDE_DIRECTORIES(
  ${CMAKE_CURRENT_SOURCE_DIR}
  ${CMAKE_CURRENT_BINARY_DIR}
  )
  
ADD_EXECUTABLE(${example_name} ${KIT_SRCS} ${KIT_MOC_CPP})
TARGET_LINK_LIBRARIES(${example_name} ${PROJECT_NAME})
