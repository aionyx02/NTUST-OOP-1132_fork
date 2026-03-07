cmake_minimum_required(VERSION 3.10)
project(FinalExam006)

enable_testing()

set(CASE_FILES case1.h case2.h case3.h case4.h case5.h)
if(NOT DEFINED INPUT_DIR)
  set(INPUT_DIR "${CMAKE_CURRENT_SOURCE_DIR}/../../solution/006")
endif()

message("INPUT_DIR=${INPUT_DIR}")
file(GLOB INPUT_SOURCE
    "${INPUT_DIR}/*.cpp"
    "${INPUT_DIR}/*.cxx"
    "${INPUT_DIR}/*.cc"
    "${INPUT_DIR}/*.c"
    "${INPUT_DIR}/*.hpp"
    "${INPUT_DIR}/*.hh"
    "${INPUT_DIR}/*.h"
  )
list(FILTER INPUT_SOURCE EXCLUDE REGEX ".*/case\\.h$")

add_custom_target(judge
  COMMAND ${CMAKE_CTEST_COMMAND} --output-on-failure
  COMMENT "Execute ctest"
)

foreach(CASE_FILE IN LISTS CASE_FILES)
  # 產生 target `*-case1`, `*-case2` ...
  string(REPLACE ".h" "" CASE_NAME ${CASE_FILE})
  set(CASE_BUILD_DIR ${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}/${CASE_NAME})
  set(TARGET_NAME "${PROJECT_NAME}-${CASE_NAME}")
  set(REPLACE_CASE_FILE ${CASE_BUILD_DIR}/case.h)
  file(MAKE_DIRECTORY ${CASE_BUILD_DIR})

  
  message("Create ${CASE_NAME} Context")
  foreach(src ${INPUT_SOURCE})
    get_filename_component(SOURCE_PATH ${src} REALPATH)
    get_filename_component(FILENAME ${src} NAME)
    set(DEST_PATH "${CASE_BUILD_DIR}/${FILENAME}")
    message(STATUS "Copy ${SOURCE_PATH} to ${DEST_PATH}")
    configure_file(${SOURCE_PATH} ${DEST_PATH} COPYONLY)
  endforeach()

  # 模擬 OnlineJudge 覆蓋檔案
  configure_file("${CMAKE_CURRENT_SOURCE_DIR}/${CASE_FILE}" "${CASE_BUILD_DIR}/case.h" COPYONLY)
  configure_file("${CMAKE_CURRENT_SOURCE_DIR}/entrypoint.cpp" "${CASE_BUILD_DIR}/entrypoint.cpp" COPYONLY)
  configure_file("${CMAKE_CURRENT_SOURCE_DIR}/test.h" "${CASE_BUILD_DIR}/test.h" COPYONLY)

  # 在獨立的目錄進行編譯
  file(GLOB CASE_CXX_SOURCES
    "${CASE_BUILD_DIR}/*.cpp"
    "${CASE_BUILD_DIR}/*.cxx"
    "${CASE_BUILD_DIR}/*.cc"
    "${CASE_BUILD_DIR}/*.c"
  )

  add_executable(${TARGET_NAME} ${CASE_CXX_SOURCES})
  add_dependencies(judge ${TARGET_NAME})
  target_include_directories(${TARGET_NAME} PRIVATE
    "${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}/${CASE_NAME}"
  )

  add_test(
    NAME "${TARGET_NAME}-testing"
    COMMAND ${TARGET_NAME}
  )
endforeach()



