set(CE_DemoGame_NAME ${PROJECT_NAME}_DemoGame)
message(STATUS "${PROJECT_NAME}::${CE_DemoGame_NAME} :: Configuring ${CE_DemoGame_NAME} v${PROJECT_VERSION}")

# directories
set(CE_DemoGame_INCLUDES_DIR ${CMAKE_CURRENT_SOURCE_DIR}/include)
set(CE_DemoGame_SOURCES_DIR ${CMAKE_CURRENT_SOURCE_DIR}/src)
set(CE_DemoGame_RESOURCES_DIR ${CMAKE_CURRENT_SOURCE_DIR}/resources)

# files
file(GLOB_RECURSE CE_DemoGame_HEADERS ${CE_DemoGame_INCLUDES_DIR}/*.hpp ${CE_DemoGame_INCLUDES_DIR}/*.h)
file(GLOB_RECURSE CE_DemoGame_SOURCES ${CE_DemoGame_SOURCES_DIR}/*.cpp)

file(GLOB_RECURSE CE_DemoGame_MESHES ${CE_DemoGame_RESOURCES_DIR}/meshes/*.obj ${CE_DemoGame_RESOURCES_DIR}/meshes/*.fbx)
file(GLOB_RECURSE CE_DemoGame_SHADERS ${CE_DemoGame_RESOURCES_DIR}/shaders/*.vert ${CE_DemoGame_RESOURCES_DIR}/shaders/*.frag)
file(GLOB_RECURSE CE_DemoGame_TEXTURES ${CE_DemoGame_RESOURCES_DIR}/textures/*.png ${CE_DemoGame_RESOURCES_DIR}/textures/*.jpg)

# executable
add_executable(${CE_DemoGame_NAME}
    ${CE_DemoGame_HEADERS} ${CE_DemoGame_SOURCES}
    ${CE_DemoGame_MESHES} ${CE_DemoGame_SHADERS}
)

# dependencies
target_link_libraries(${CE_DemoGame_NAME} PUBLIC ${PROJECT_NAME})

# folder
if (NOT CondorEngine_IS_ROOT_PROJECT)
    set_target_properties(${CE_DemoGame_NAME} PROPERTIES FOLDER "Engine")
endif()
