#--------------------------------------------------------------------
# Tools
#--------------------------------------------------------------------

# Override output directories for tools
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/tools/bin)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/tools/bin)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/tools/bin/lib)

# Tools
add_subdirectory(copy_resources)
add_subdirectory(shader_preprocessor)
