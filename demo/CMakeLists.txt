set(CE_Demo_NAME ${PROJECT_NAME}_Demo)
message(STATUS "${PROJECT_NAME}::${CE_Demo_NAME} :: Configuring ${CE_Demo_NAME} v${PROJECT_VERSION}")

# directories
set(CE_Demo_INCLUDES_DIR ${CMAKE_CURRENT_SOURCE_DIR}/include)
set(CE_Demo_SOURCES_DIR ${CMAKE_CURRENT_SOURCE_DIR}/src)
set(CE_Demo_RESOURCES_DIR ${CMAKE_CURRENT_SOURCE_DIR}/resources)

# files
file(GLOB_RECURSE CE_Demo_HEADERS ${CE_Demo_INCLUDES_DIR}/*.hpp ${CE_Demo_INCLUDES_DIR}/*.h)
file(GLOB_RECURSE CE_Demo_SOURCES ${CE_Demo_SOURCES_DIR}/*.cpp)

file(GLOB_RECURSE CE_Demo_MESHES ${CE_Demo_RESOURCES_DIR}/meshes/*.obj ${CE_Demo_RESOURCES_DIR}/meshes/*.fbx)
file(GLOB_RECURSE CE_Demo_SHADERS ${CE_Demo_RESOURCES_DIR}/shaders/*.vert ${CE_Demo_RESOURCES_DIR}/haders/*.frag)
file(GLOB_RECURSE CE_Demo_TEXTURES ${CE_Demo_RESOURCES_DIR}/textures/*.png ${CE_Demo_RESOURCES_DIR}/textures/*.jpg)

# executable
add_executable(${CE_Demo_NAME}
    ${CE_Demo_HEADERS} ${CE_Demo_SOURCES}
    ${CE_Demo_MESHES} ${CE_Demo_SHADERS}
)

# dependencies
target_link_libraries(${CE_Demo_NAME} PUBLIC ${PROJECT_NAME})

# folder
if (NOT CondorEngine_IS_ROOT_PROJECT)
    set_target_properties(${CE_Demo_NAME} PROPERTIES FOLDER "Engine")
endif()
