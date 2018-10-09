cmake_minimum_required(VERSION 3.12)

set(CMAKE_DISABLE_IN_SOURCE_BUILD ON)
set(CMAKE_DISABLE_SOURCE_CHANGES ON)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} ${CMAKE_CURRENT_SOURCE_DIR}/cmake)
include(ClangFormat)
include(LLVM)

# Setup LLVM.
bootstrap_llvm("release_70")
find_package(LLVM REQUIRED CONFIG)
find_package(Clang REQUIRED)

# Project definition.
project(Crowbarella LANGUAGES CXX)

# Locate sources.
file(GLOB_RECURSE SOURCE_FILES RELATIVE "${CMAKE_CURRENT_SOURCE_DIR}" "src/*.cpp")
file(GLOB_RECURSE HEADER_FILES RELATIVE "${CMAKE_CURRENT_SOURCE_DIR}" "src/*.h")

# Add target definition.
add_executable(${PROJECT_NAME} ${HEADER_FILES} ${SOURCE_FILES})
target_link_libraries(${PROJECT_NAME} PRIVATE clangTooling )
target_compile_definitions(${PROJECT_NAME} PRIVATE ${LLVM_DEFINITIONS} ${CLANG_DEFINITIONS})
target_include_directories(${PROJECT_NAME} PRIVATE ${LLVM_INCLUDE_DIRS} ${CLANG_INCLUDE_DIRS})

# Format sources.
target_clang_format(${PROJECT_NAME}
  STYLE "${CMAKE_SOURCE_DIR}/.clang-format"
  FILES ${HEADER_FILES} ${SOURCE_FILES})
