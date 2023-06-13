set(example_name google)

set(KIT_SRCS
  google.cpp
  google.h
  main.cpp
  )

set(KIT_MOC_SRCS
  google.h
  )

QT4_WRAP_CPP(KIT_MOC_CPP ${KIT_MOC_SRCS})

include_directories(
  ${CMAKE_CURRENT_SOURCE_DIR}
  ${CMAKE_CURRENT_BINARY_DIR}
  )

add_executable(${example_name} ${KIT_SRCS} ${KIT_MOC_CPP})
target_link_libraries(${example_name} ${PROJECT_NAME})
