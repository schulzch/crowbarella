cmake_minimum_required(VERSION 3.12)

include(ExternalProject)

project(llvm)

option(LLVM_TAG "Git branch name, commit id or tag")

# Download step.
ExternalProject_Add(llvm-download
  GIT_REPOSITORY http://llvm.org/git/llvm.git
  GIT_TAG ${LLVM_TAG}
  SOURCE_DIR "${CMAKE_BINARY_DIR}/src"
  BINARY_DIR "${CMAKE_BINARY_DIR}/build"
  CONFIGURE_COMMAND ""
  BUILD_COMMAND ""
  INSTALL_COMMAND ""
  TEST_COMMAND "")
ExternalProject_Add(clang-download
  DEPENDS llvm-download
  GIT_REPOSITORY http://llvm.org/git/clang.git
  GIT_TAG ${LLVM_TAG}
  SOURCE_DIR "${CMAKE_BINARY_DIR}/src/tools/clang"
  BINARY_DIR "${CMAKE_BINARY_DIR}/build"
  CONFIGURE_COMMAND ""
  BUILD_COMMAND ""
  INSTALL_COMMAND ""
  TEST_COMMAND "")

# Non-download steps.
ExternalProject_Add(llvm
  DEPENDS llvm-download clang-download
  DOWNLOAD_COMMAND ""
  UPDATE_COMMAND ""
  SOURCE_DIR "${CMAKE_BINARY_DIR}/src/"
  INSTALL_DIR "${CMAKE_BINARY_DIR}/build/"
  CMAKE_ARGS
    # LLVM-specific.
    "-DLLVM_TARGETS_TO_BUILD:STRING=X86"
    "-DLLVM_BUILD_TOOLS:BOOL=OFF"
    "-DLLVM_BUILD_UTILS:BOOL=OFF"
    "-DLLVM_INCLUDE_BENCHMARKS:BOOL=OFF"
    "-DLLVM_INCLUDE_EXAMPLES:BOOL=OFF"
    "-DLLVM_INCLUDE_TESTS:BOOL=OFF"
    "-DLLVM_INCLUDE_DOCS:BOOL=OFF"
    # Clang-specific.
    "-DCLANG_BUILD_TOOLS:BOOL=OFF"
    # CMake-related.
    "-G${CMAKE_GENERATOR}"
    "-DCMAKE_TOOLCHAIN_FILE=${CMAKE_TOOLCHAIN_FILE}"
    "-DCMAKE_INSTALL_PREFIX:PATH=<INSTALL_DIR>")
