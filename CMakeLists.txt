cmake_minimum_required(VERSION 3.22.0)

get_property(GENERATOR_IS_MULTI_CONFIG GLOBAL
             PROPERTY GENERATOR_IS_MULTI_CONFIG)
if(NOT GENERATOR_IS_MULTI_CONFIG)
  set(CMAKE_BUILD_TYPE
      Debug
      CACHE STRING "Build type")
  message(STATUS "CMAKE_BUILD_TYPE: ${CMAKE_BUILD_TYPE}")
endif()
message(STATUS "CMAKE_VERSION: ${CMAKE_VERSION}")

project(aoc2021 CXX)

set(CMAKE_INSTALL_MESSAGE LAZY)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set_property(GLOBAL PROPERTY GLOBAL_DEPENDS_NO_CYCLES ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_INCLUDE_CURRENT_DIR TRUE)
set(CMAKE_CXX_VISIBILITY_PRESET hidden)
set(CMAKE_VISIBILITY_INLINES_HIDDEN ON)
list(APPEND CMAKE_MODULE_PATH ${CMAKE_CURRENT_LIST_DIR})

list(APPEND CMAKE_MODULE_PATH ${CMAKE_CURRENT_LIST_DIR})
include(ConanConfig.cmake)

macro(find_conan_package PKG)
  find_package(${PKG} CONFIG REQUIRED PATHS ${CMAKE_BINARY_DIR}/conan
               NO_DEFAULT_PATH)
endmacro()

find_conan_package(range-v3)
find_conan_package(fmt)

function(add_day_executable TARGET)
  add_executable(${TARGET} ${ARGN})
  target_link_libraries(${TARGET} PRIVATE fmt::fmt-header-only
                                          range-v3::range-v3)
  if(CMAKE_CXX_COMPILER_ID STREQUAL GNU)
    target_compile_options(
      ${TARGET} PRIVATE -Wpedantic -Wall -Wextra -Wconversion -Wsign-conversion
                        -Werror)
  endif()
endfunction()

add_day_executable(day1 day1.cxx)
add_day_executable(day1_constexpr day1_constexpr.cxx)
