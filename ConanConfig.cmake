if(NOT EXISTS "${CMAKE_BINARY_DIR}/conan.cmake")
  message(
    STATUS
      "Downloading conan.cmake from https://github.com/conan-io/cmake-conan")
  file(
    DOWNLOAD
    "https://raw.githubusercontent.com/conan-io/cmake-conan/v0.16.1/conan.cmake"
    "${CMAKE_BINARY_DIR}/conan.cmake"
    EXPECTED_HASH
      SHA256=396e16d0f5eabdc6a14afddbcfff62a54a7ee75c6da23f32f7a31bc85db23484
    TLS_VERIFY ON)
endif()

include(${CMAKE_BINARY_DIR}/conan.cmake)

conan_check(VERSION 1.42.2 REQUIRED)

if(GENERATOR_IS_MULTI_CONFIG)
  set(CONAN_BUILD_TYPE_INPUT "")
else()
  if(CMAKE_BUILD_TYPE STREQUAL Debug)
    set(CONAN_BUILD_TYPE_INPUT BUILD_TYPE Debug)
  else()
    set(CONAN_BUILD_TYPE_INPUT BUILD_TYPE Release)
  endif()
endif()

set(CONAN_ENV "")
if(NOT MSVC)
  set(CONAN_ENV ENV "CC=${CMAKE_C_COMPILER}" "CXX=${CMAKE_CXX_COMPILER}")
endif()

set(CONAN_REQUIRES fmt/8.0.1@ range-v3/0.11.0@)
set(CONAN_OPTIONS fmt:header_only=True)

conan_cmake_run(
  CONAN_COMMAND
  ${CONAN_CMD}
  REQUIRES
  ${CONAN_REQUIRES}
  OPTIONS
  ${CONAN_OPTIONS}
  BUILD
  missing
  ${CONAN_BUILD_TYPE_INPUT}
  ${CONAN_ENV}
  INSTALL_FOLDER
  ${CMAKE_BINARY_DIR}/conan
  GENERATORS
  cmake_find_package_multi)

if(GENERATOR_IS_MULTI_CONFIG)
  foreach(CMAKE_BUILD_TYPE Release Debug)
    conan_set_find_paths()
  endforeach()
else()
  conan_set_find_paths()
endif()
