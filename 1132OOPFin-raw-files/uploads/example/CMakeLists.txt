cmake_minimum_required(VERSION 3.10)

project(testlib)

set(TARGET testlib-example)

file(GLOB CXX_SOURCES
  "${CMAKE_CURRENT_SOURCE_DIR}/*.cxx"
  "${CMAKE_CURRENT_SOURCE_DIR}/*.cpp"
  "${CMAKE_CURRENT_SOURCE_DIR}/*.cc"
  "${CMAKE_CURRENT_SOURCE_DIR}/*.c"
)

foreach(src ${SOURCES})
  message(STATUS "${src}")
endforeach()


add_executable(${TARGET} ${CXX_SOURCES})

target_include_directories(${TARGET}
  PRIVATE
  "${CMAKE_CURRENT_SOURCE_DIR}"
  "${CMAKE_CURRENT_SOURCE_DIR}/include"
  "${CMAKE_CURRENT_SOURCE_DIR}/shared"
)
