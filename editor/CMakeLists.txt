#--------------------------------------------------------------------
# CondorEngine Editor
#--------------------------------------------------------------------
set(Editor_NAME CondorEditor)
message(STATUS "${PROJECT_NAME} :: Configuring editor...")
set(CondorEditor_THIRD_PARTY_DIR ${CMAKE_CURRENT_SOURCE_DIR}/thirdparty)

# Override output directories for editor
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/editor/bin)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/editor/bin)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/editor/bin/lib)

# Third Party Libraries
#--------------------------------------------------------------------

# yaml-cpp
add_subdirectory(${CondorEditor_THIRD_PARTY_DIR}/yaml-cpp)
set_target_properties(yaml-cpp PROPERTIES FOLDER "EngineLibs")
set_target_properties(yaml-cpp-parse PROPERTIES FOLDER "EngineLibs/yaml-cpp")
set_target_properties(yaml-cpp-read PROPERTIES FOLDER "EngineLibs/yaml-cpp")
set_target_properties(yaml-cpp-sandbox PROPERTIES FOLDER "EngineLibs/yaml-cpp")

# Main
#--------------------------------------------------------------------

# files
file(GLOB_RECURSE CondorEditor_HEADERS ${CMAKE_CURRENT_SOURCE_DIR}/include/*.hpp ${CMAKE_CURRENT_SOURCE_DIR}/include/*.h)
file(GLOB_RECURSE CondorEditor_SOURCES ${CMAKE_CURRENT_SOURCE_DIR}/src/*cpp)

# executable
add_executable(${Editor_NAME}
    ${CondorEditor_HEADERS} 
    ${CondorEditor_SOURCES}
)
target_include_directories(${PROJECT_NAME} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)

# dependencies
target_link_libraries(${Editor_NAME} PUBLIC ${PROJECT_NAME})
target_link_libraries(${Editor_NAME} PUBLIC imgui)
target_link_libraries(${Editor_NAME} PUBLIC yaml-cpp)
set_property(TARGET ${Editor_NAME} PROPERTY
    MSVC_RUNTIME_LIBRARY "MultiThreadedDLL"
)

# Copy runtime dependencies (DLLs) next to the editor executable so it can run
# without requiring the user to modify PATH after each build.
add_custom_command(TARGET ${Editor_NAME} POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E make_directory $<TARGET_FILE_DIR:${Editor_NAME}>
    COMMAND ${CMAKE_COMMAND} -E copy_directory
        "${CMAKE_SOURCE_DIR}/bin/Windows/x64/$<CONFIG>"
        $<TARGET_FILE_DIR:${Editor_NAME}>
)

# folder
if (NOT CondorEngine_IS_ROOT_PROJECT)
    set_target_properties(${Editor_NAME} PROPERTIES FOLDER "Engine")
endif()
