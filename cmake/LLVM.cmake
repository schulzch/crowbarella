set(DIR_OF_CMAKE "${CMAKE_CURRENT_LIST_DIR}")

# Bootstrap LLVM at configure stage.
function(bootstrap_llvm LLVM_TAG)
  # Set source and build directory.
  set(LIST_DIR "${DIR_OF_CMAKE}/llvm/")
  set(BUILD_DIR "${CMAKE_BINARY_DIR}/llvm-build/")
  # Set variable for find_package().
  set(LLVM_ROOT "${BUILD_DIR}/build/lib/cmake/llvm")
  set(LLVM_ROOT ${LLVM_ROOT} PARENT_SCOPE)
  set(Clang_ROOT "${BUILD_DIR}/build/lib/cmake/clang")
  set(Clang_ROOT ${Clang_ROOT} PARENT_SCOPE)
  if(NOT EXISTS "${LLVM_ROOT}/LLVMConfig.cmake")
    message(STATUS "LLVM tag: ${LLVM_TAG}")
    file(MAKE_DIRECTORY ${BUILD_DIR})
    # Configure LLVM.
    execute_process(
      COMMAND ${CMAKE_COMMAND} ${LIST_DIR}
        "-G${CMAKE_GENERATOR}"
        "-DCMAKE_TOOLCHAIN_FILE=${CMAKE_TOOLCHAIN_FILE}"
        "-DLLVM_TAG:STRING=${LLVM_TAG}"
      WORKING_DIRECTORY ${BUILD_DIR}
      OUTPUT_QUIET
      RESULT_VARIABLE retcode)
    if(NOT "${retcode}" STREQUAL "0")
      message(FATAL_ERROR "Fatal error while configuring LLVM.")
    endif()
    # Build LLVM.
    execute_process(
      COMMAND ${CMAKE_COMMAND} --build . --parallel
        WORKING_DIRECTORY ${BUILD_DIR})
  else()
    message(STATUS "LLVM tag: ${LLVM_TAG} (cached)")
  endif()
endfunction(bootstrap_llvm)
