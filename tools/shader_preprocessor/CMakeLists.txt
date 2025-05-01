#--------------------------------------------------------------------
# Tool: Shader Preprocessor
#--------------------------------------------------------------------

# preprocessor executable
set(CE_Tool_SP_NAME ${PROJECT_NAME}_ShaderPreprocessor)
add_executable(${CE_Tool_SP_NAME} shader_preprocessor.cpp)

# shader source files
file(GLOB_RECURSE ENGINE_SHADER_SOURCES "${CMAKE_SOURCE_DIR}/shaders/*.frag" "${CMAKE_SOURCE_DIR}/shaders/*.vert")
file(GLOB_RECURSE SHADER_SOURCES "${CMAKE_SOURCE_DIR}/shaders/*.frag" "${CMAKE_SOURCE_DIR}/shaders/*.vert")

# preprocessor commands
set(PREPROCESSED_SHADERS "")
foreach(SHADER ${ENGINE_SHADER_SOURCES})
    get_filename_component(SHADER_NAME ${SHADER} NAME)
    set(OUT_SHADER "${CondorEngine_FULL_OUTPUT_DIR}/$<CONFIG>/CondorEngine/shaders/${SHADER_NAME}")
    add_custom_command(
        OUTPUT ${OUT_SHADER}
        COMMAND ${CMAKE_COMMAND} -E make_directory ${CondorEngine_FULL_OUTPUT_DIR}/$<CONFIG>/CondorEngine/shaders
        COMMAND ${CE_Tool_SP_NAME} ${SHADER} ${OUT_SHADER}
        DEPENDS ${SHADER} ${CE_Tool_SP_NAME}
        COMMENT "Preprocessing ${SHADER_NAME}"
    )
    list(APPEND PREPROCESSED_SHADERS ${OUT_SHADER})
endforeach()
if (NOT CondorEngine_IS_ROOT_PROJECT)
    foreach(SHADER ${SHADER_SOURCES})
        get_filename_component(SHADER_NAME ${SHADER} NAME)
        set(OUT_SHADER "${CondorEngine_FULL_OUTPUT_DIR}/$<CONFIG>/shaders/${SHADER_NAME}")
        add_custom_command(
            OUTPUT ${OUT_SHADER}
            COMMAND ${CMAKE_COMMAND} -E make_directory ${CondorEngine_FULL_OUTPUT_DIR}/$<CONFIG>/shaders
            COMMAND ${CE_Tool_SP_NAME} ${SHADER} ${OUT_SHADER}
            DEPENDS ${SHADER} ${CE_Tool_SP_NAME}
            COMMENT "Preprocessing ${SHADER_NAME}"
        )
        list(APPEND PREPROCESSED_SHADERS ${OUT_SHADER})
    endforeach()
endif()

# preprocessor target
set(CE_Tool_PS_NAME ${PROJECT_NAME}_ProcessShaders)
add_custom_target(${CE_Tool_PS_NAME} ALL DEPENDS ${PREPROCESSED_SHADERS})

# cmake folder
if (NOT CondorEngine_IS_ROOT_PROJECT)
    set_target_properties(${CE_Tool_SP_NAME} PROPERTIES FOLDER "Engine/Tools")
    set_target_properties(${CE_Tool_PS_NAME} PROPERTIES FOLDER "Engine/Tools")
else()
    set_target_properties(${CE_Tool_SP_NAME} PROPERTIES FOLDER "Tools")
    set_target_properties(${CE_Tool_PS_NAME} PROPERTIES FOLDER "Tools")
endif()
