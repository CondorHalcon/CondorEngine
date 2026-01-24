set(CE_DemoGame_NAME ${PROJECT_NAME}_DemoGame)
message(STATUS "${PROJECT_NAME} :: Configuring ${CE_DemoGame_NAME}...")

# directories
set(CE_DemoGame_INCLUDES_DIR ${CMAKE_CURRENT_SOURCE_DIR}/include)
set(CE_DemoGame_SOURCES_DIR ${CMAKE_CURRENT_SOURCE_DIR}/src)
set(CE_DemoGame_RESOURCES_DIR ${CMAKE_CURRENT_SOURCE_DIR}/resources)

# files
file(GLOB_RECURSE CE_DemoGame_HEADERS ${CE_DemoGame_INCLUDES_DIR}/*.hpp ${CE_DemoGame_INCLUDES_DIR}/*.h)
file(GLOB_RECURSE CE_DemoGame_SOURCES ${CE_DemoGame_SOURCES_DIR}/*.cpp)
file(GLOB_RECURSE CE_DemoGame_SHADERS ${CE_DemoGame_RESOURCES_DIR}/shaders/*.vert ${CE_DemoGame_RESOURCES_DIR}/shaders/*.frag)

# executable
add_executable(${CE_DemoGame_NAME}
    ${CE_DemoGame_HEADERS} 
    ${CE_DemoGame_SOURCES}
    ${CE_DemoGame_SHADERS}
)
target_include_directories(${PROJECT_NAME} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)

# dependencies
target_link_libraries(${CE_DemoGame_NAME} PUBLIC ${PROJECT_NAME})

# copy resources
message(STATUS "${PROJECT_NAME} :: Adding demo resource directory ${CMAKE_CURRENT_SOURCE_DIR}/resources...")
add_custom_command(
    TARGET ${CE_DemoGame_NAME} POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
    ${CMAKE_CURRENT_SOURCE_DIR}/resources
    ${CMAKE_LIBRARY_OUTPUT_DIRECTORY}/$<CONFIG>
    COMMENT "${PROJECT_NAME} :: Copying resources ${CMAKE_CURRENT_SOURCE_DIR}/resources..."
)

# folder
if (NOT CondorEngine_IS_ROOT_PROJECT)
    set_target_properties(${CE_DemoGame_NAME} PROPERTIES FOLDER "Engine")
endif()
