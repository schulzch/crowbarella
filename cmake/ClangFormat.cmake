include(CMakeParseArguments)

function(target_clang_format TARGET)
  cmake_parse_arguments(args "" "STYLE" "FILES" ${ARGN})

  if(args_STYLE)
    get_filename_component(CFG_FILE ${args_STYLE} ABSOLUTE)
    set(STYLE "-style=file")
    set(STYLE_FILE "-assume-filename=${CFG_FILE}")
  endif()

  list(REMOVE_DUPLICATES args_FILES)
  list(SORT args_FILES)

  find_program(CLANG_FORMAT clang-format)

  if(CLANG_FORMAT)
    # Query for version.
    execute_process(
      COMMAND ${CLANG_FORMAT} "--version"
      OUTPUT_VARIABLE CLANG_FORMAT_VERSION
      OUTPUT_STRIP_TRAILING_WHITESPACE)
    string(REGEX MATCH "[0-9]+\\.[0-9]+\\.[0-9]+" CLANG_FORMAT_VERSION ${CLANG_FORMAT_VERSION})
  endif()

  set(CLANG_FORMAT_VERSION_PATTERN "(6|7).[0-9]+.[0-9]+")

  if(CLANG_FORMAT AND CLANG_FORMAT_VERSION MATCHES ${CLANG_FORMAT_VERSION_PATTERN})
    add_custom_command(TARGET ${TARGET}
      PRE_BUILD
      COMMAND ${CLANG_FORMAT}
        "-fallback-style=none"
        "-i"
        ${STYLE}
        ${STYLE_FILE}
        ${args_FILES}
      WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
      COMMENT "Format target ${TARGET}"
      VERBATIM)
  elseif(CLANG_FORMAT)
    message(WARNING "clang-format version ${CLANG_FORMAT_VERSION} is unsuitable."
      " Install a version matching \"${CLANG_FORMAT_VERSION_PATTERN}\" to enable formatting.")
  else()
    message(STATUS "clang-format: not found")
  endif()
endfunction(target_clang_format)
