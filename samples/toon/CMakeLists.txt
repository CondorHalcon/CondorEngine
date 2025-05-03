#--------------------------------------------------------------------
# Sample :: Toon
#--------------------------------------------------------------------
set (CE_Sample_Toon_NAME ${PROJECT_NAME}_SampleToon)
message(STATUS "${PROJECT_NAME} :: Configuring ${CE_Sample_Toon_NAME}...")

# source files
file(GLOB_RECURSE CE_Sample_Toon_SOURCES ${CMAKE_CURRENT_SOURCE_DIR}/*.cpp)
file(GLOB_RECURSE CE_Sample_Toon_SHADERS ${CMAKE_CURRENT_SOURCE_DIR}/shaders/*.frag)

# executable
add_executable(${CE_Sample_Toon_NAME} EXCLUDE_FROM_ALL
    ${CE_Sample_Toon_SOURCES}
    ${CE_Sample_Toon_SHADERS}
)

# dependencies
target_link_libraries(${CE_Sample_Toon_NAME} PUBLIC ${PROJECT_NAME})

# copy resources
message(STATUS "${PROJECT_NAME} :: Adding sample resource directory ${CMAKE_CURRENT_SOURCE_DIR}/resources...")
add_custom_command(
    TARGET ${CE_Sample_Toon_NAME} POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
    ${CMAKE_CURRENT_SOURCE_DIR}/resources
    ${CMAKE_LIBRARY_OUTPUT_DIRECTORY}/$<CONFIG>
    COMMENT "Copying resources ${CMAKE_CURRENT_SOURCE_DIR}/resources..."
)

# preprocess shaders
set(PREPROCESSED_SHADERS "")
message(STATUS "${PROJECT_NAME} :: Adding sample shaders in directory ${CMAKE_CURRENT_SOURCE_DIR}/shaders...")
foreach(SHADER ${CE_Sample_Toon_SHADERS})
    get_filename_component(SHADER_NAME ${SHADER} NAME)
    set(OUT_SHADER "${CondorEngine_FULL_OUTPUT_DIR}/$<CONFIG>/shaders/${SHADER_NAME}")
    add_custom_command(
        OUTPUT ${OUT_SHADER}
        COMMAND ${CMAKE_COMMAND} -E make_directory ${CondorEngine_FULL_OUTPUT_DIR}/$<CONFIG>/shaders
        COMMAND ${SHADER_PREPROCESSOR} ${SHADER} ${OUT_SHADER} ${CondorEngine_SOURCE_DIR}/shaders
        DEPENDS ${SHADER} CondorEngine_ShaderPreprocessor
        COMMENT "Preprocessing ${SHADER_NAME}"
    )
    list(APPEND PREPROCESSED_SHADERS ${OUT_SHADER})
endforeach()

# preprocess shader target
set(CE_Sample_ToonShaders_NAME ${CE_Sample_Toon_NAME}Shaders)
add_custom_target(${CE_Sample_ToonShaders_NAME} DEPENDS ${PREPROCESSED_SHADERS})
add_dependencies(${CE_Sample_Toon_NAME} ${CE_Sample_ToonShaders_NAME})

# cmake folder
if (NOT CondorEngine_IS_ROOT_PROJECT)
    set_target_properties(${CE_Sample_Toon_NAME} PROPERTIES FOLDER "Engine/Samples")
    set_target_properties(${CE_Sample_ToonShaders_NAME} PROPERTIES FOLDER "Engine/Samples")
else()
    set_target_properties(${CE_Sample_Toon_NAME} PROPERTIES FOLDER "Samples")
    set_target_properties(${CE_Sample_ToonShaders_NAME} PROPERTIES FOLDER "Samples")
endif()
