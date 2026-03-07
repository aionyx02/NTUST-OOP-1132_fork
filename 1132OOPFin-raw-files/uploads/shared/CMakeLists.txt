cmake_minimum_required(VERSION 3.10)
project(FinalExam001)

set(CASE_FILES case1.h case2.h case3.h case4.h case5.h)
# if(NOT DEFINED INPUT_DIR)
#   set(INPUT_DIR "${CMAKE_CURRENT_SOURCE_DIR}/../../solution/001")
# endif()

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

foreach(src ${INPUT_SOURCE})
  message(STATUS ${src})
endforeach()

foreach(CASE_FILE IN LISTS CASE_FILES)
  # 產生 target `*-case1`, `*-case2` ...
  string(REPLACE ".h" "" CASE_NAME ${CASE_FILE})
  set(CASE_BUILD_DIR ${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}/${CASE_NAME})
  set(TARGET_NAME "${PROJECT_NAME}-${CASE_NAME}")
  set(REPLACE_CASE_FILE ${CASE_BUILD_DIR}/case.h)
  file(MAKE_DIRECTORY ${CASE_BUILD_DIR})

  
  foreach(src ${INPUT_SOURCE})
    get_filename_component(filename ${src} NAME)
    configure_file(
      ${src}
      ${CASE_BUILD_DIR}/${filename}
      COPYONLY
    )
  endforeach()

  # 模擬 OnlineJudge 的覆蓋檔案
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

  target_include_directories(${TARGET_NAME} PRIVATE
    "${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}/${CASE_NAME}"
  )
endforeach()
