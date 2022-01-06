cmake_minimum_required(VERSION 3.15)


set(ProjectName test)

project(${ProjectName} CXX)
include(./src/cmake/StandardProjectSettings.cmake)
include(./src/cmake/PreventInSourceBuilds.cmake)

add_library(project_options INTERFACE)
target_compile_features(project_options INTERFACE cxx_std_20)

if(CMAKE_CXX_COMPILER_ID MATCHES ".*Clang")
  option(ENABLE_BUILD_WITH_TIME_TRACE "Enable -ftime-trace to generate time tracing .json files on clang" OFF)
  if(ENABLE_BUILD_WITH_TIME_TRACE)
    target_compile_options(project_options INTERFACE -ftime-trace)
  endif()
endif()

add_library(project_warnings INTERFACE)

include(./src/cmake/Cache.cmake)

include(./src/cmake/Linker.cmake)
configure_linker(project_options)

include(./src/cmake/CompilerWarnings.cmake)
set_project_warnings(project_warnings)

include(./src/cmake/Sanitizers.cmake)
enable_sanitizers(project_options)

include(./src/cmake/StaticAnalyzers.cmake)

option(ENABLE_PCH "Enable Precompiled Headers" ON)
if(ENABLE_PCH)
  target_precompile_headers(
    project_options
    INTERFACE
    <vector>
    <string>
    <iostream>
    <type_traits>
    <map>
    <list>
    <optional>
    <stdexcept>
    <utility>)
endif()


add_executable(${ProjectName} ./src/main.cpp)

target_link_libraries(${ProjectName} project_options project_warnings)
