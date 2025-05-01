#--------------------------------------------------------------------
# Sample :: Toon
#--------------------------------------------------------------------
set (CE_Sample_Toon_NAME ${PROJECT_NAME}_SampleToon)
message(STATUS "${PROJECT_NAME}::${CE_Sample_Toon_NAME} :: Configuring ${CE_Sample_Toon_NAME} v${PROJECT_VERSION}")

file(GLOB_RECURSE CE_Sample_Toon_SOURCES ${${CMAKE_CURRENT_SOURCE_DIR}}/*.cpp)
file(GLOB_RECURSE CE_Sample_Toon_SHADERS ${${CMAKE_CURRENT_SOURCE_DIR}}/resources/shaders/*.frag)

add_executable(${CE_Sample_Toon_NAME}
    ${CE_Sample_Toon_SOURCES}
    ${CE_Sample_Toon_SHADERS}
)
add_custom_command(
    TARGET ${CE_Sample_Toon_NAME} POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
    ${${CMAKE_CURRENT_SOURCE_DIR}}/resources
    ${CMAKE_LIBRARY_OUTPUT_DIRECTORY}/$<CONFIG>
)
target_link_libraries(${CE_Sample_Toon_NAME} PUBLIC ${PROJECT_NAME})
if (NOT CondorEngine_IS_ROOT_PROJECT)
    set_target_properties(${CE_Sample_Toon_NAME} PROPERTIES FOLDER "Engine/Samples")
else()
    set_target_properties(${CE_Sample_Toon_NAME} PROPERTIES FOLDER "Samples")
endif()
