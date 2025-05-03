#--------------------------------------------------------------------
# Tool: Copy Resources
#--------------------------------------------------------------------
set(CE_Tool_CR_NAME ${PROJECT_NAME}_CopyResources)
message(STATUS "${PROJECT_NAME} :: Configuring ${CE_Tool_CR_NAME}...")
add_custom_target(${CE_Tool_CR_NAME} ALL)

message(STATUS "${PROJECT_NAME} :: Adding engine resource directory ${CondorEngine_SOURCE_DIR}/resources...")
add_custom_command(
    TARGET ${CE_Tool_CR_NAME} PRE_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
    ${CondorEngine_SOURCE_DIR}/resources
    ${CondorEngine_FULL_OUTPUT_DIR}/$<CONFIG>/CondorEngine
)
if (NOT CondorEngine_IS_ROOT_PROJECT)
    message(STATUS "${PROJECT_NAME} :: Adding resource directory ${CMAKE_SOURCE_DIR}/resources...")
    add_custom_command(
        TARGET ${CE_Tool_CR_NAME} PRE_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_directory
        ${CMAKE_SOURCE_DIR}/resources
        ${CondorEngine_FULL_OUTPUT_DIR}/$<CONFIG>
    )
endif()

if (NOT CondorEngine_IS_ROOT_PROJECT)
    set_target_properties(${CE_Tool_CR_NAME} PROPERTIES FOLDER "Engine/Tools")
else()
    set_target_properties(${CE_Tool_CR_NAME} PROPERTIES FOLDER "Tools")
endif()
