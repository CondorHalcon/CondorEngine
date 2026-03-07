#--------------------------------------------------------------------
# CondorEngine
#--------------------------------------------------------------------
message(STATUS "${PROJECT_NAME} :: Configuring engine third party libraries")
set(CondorEngine_THIRD_PARTY_DIR ${CMAKE_CURRENT_SOURCE_DIR}/thirdparty)

# Third Party Libraries
#--------------------------------------------------------------------

# assimp
add_subdirectory(${CondorEngine_THIRD_PARTY_DIR}/assimp)
set_target_properties(assimp PROPERTIES FOLDER "EngineLibs")
set_target_properties(UpdateAssimpLibsDebugSymbolsAndDLLs PROPERTIES FOLDER "EngineLibs/assimp_utils")
set_target_properties(uninstall PROPERTIES FOLDER "EngineLibs/assimp_utils")
set_target_properties(unit PROPERTIES FOLDER "EngineLibs/assimp_utils")
set_target_properties(zlibstatic PROPERTIES FOLDER "EngineLibs/assimp_utils")

# glad
message(STATUS "GLEW :: Importing lib")
add_library(glad STATIC 
    ${CondorEngine_THIRD_PARTY_DIR}/glad/src/glad.c
)
target_include_directories(glad PUBLIC ${CondorEngine_THIRD_PARTY_DIR}/glad/include)
set_target_properties(glad PROPERTIES FOLDER "EngineLibs")

# glfw
set(GLFW_LIBRARY_TYPE STATIC)
add_subdirectory(${CondorEngine_THIRD_PARTY_DIR}/glfw)
set_target_properties(glfw PROPERTIES FOLDER "EngineLibs")
if (docs)
    set_target_properties(docs PROPERTIES FOLDER "EngineLibs/glfw_utils")
endif()
set_target_properties(update_mappings PROPERTIES FOLDER "EngineLibs/glfw_utils")

# glm - force static library to avoid building a shared DLL
# Temporarily disable BUILD_SHARED_LIBS so GLM's add_library() uses STATIC.
if(DEFINED BUILD_SHARED_LIBS)
    set(_OLD_BUILD_SHARED_LIBS ${BUILD_SHARED_LIBS})
else()
    set(_OLD_BUILD_SHARED_LIBS "")
endif()
set(BUILD_SHARED_LIBS OFF)
add_subdirectory(${CondorEngine_THIRD_PARTY_DIR}/glm)
if(_OLD_BUILD_SHARED_LIBS)
    set(BUILD_SHARED_LIBS ${_OLD_BUILD_SHARED_LIBS})
else()
    unset(BUILD_SHARED_LIBS)
endif()
set_target_properties(glm PROPERTIES FOLDER "EngineLibs")

# imgui
add_library(imgui STATIC
    ${CondorEngine_THIRD_PARTY_DIR}/imgui/imgui.cpp
    ${CondorEngine_THIRD_PARTY_DIR}/imgui/imgui_draw.cpp
    ${CondorEngine_THIRD_PARTY_DIR}/imgui/imgui_tables.cpp
    ${CondorEngine_THIRD_PARTY_DIR}/imgui/imgui_widgets.cpp
    ${CondorEngine_THIRD_PARTY_DIR}/imgui/backends/imgui_impl_glfw.cpp
    ${CondorEngine_THIRD_PARTY_DIR}/imgui/backends/imgui_impl_opengl3.cpp
)
target_include_directories(imgui PUBLIC
    ${CondorEngine_THIRD_PARTY_DIR}/imgui
    ${CondorEngine_THIRD_PARTY_DIR}/imgui/backends
)
target_link_libraries(imgui PUBLIC glfw)
target_compile_definitions(imgui PUBLIC IMGUI_ENABLE_DOCKING)
target_compile_definitions(imgui PUBLIC IMGUI_USER_CONFIG="${CondorEngine_THIRD_PARTY_DIR}/imconfig.h")
set_property(TARGET imgui PROPERTY
    MSVC_RUNTIME_LIBRARY "MultiThreadedDLL"
)
set_target_properties(imgui PROPERTIES FOLDER "EngineLibs")

# OpenGL
find_package(OpenGL REQUIRED)

# Main
#--------------------------------------------------------------------
message(STATUS "${PROJECT_NAME} :: Configuring engine...")

# files
file(GLOB_RECURSE CondorEngine_HEADERS ${CMAKE_CURRENT_SOURCE_DIR}/include/*.hpp ${CMAKE_CURRENT_SOURCE_DIR}/include/*.h)
file(GLOB_RECURSE CondorEngine_SOURCES ${CMAKE_CURRENT_SOURCE_DIR}/src/*cpp)
file(GLOB_RECURSE CondorEngine_SHADERS ${CMAKE_CURRENT_SOURCE_DIR}/shaders/*.vert ${CMAKE_CURRENT_SOURCE_DIR}/shaders/*.frag)
file(GLOB_RECURSE CondorEngine_SHADER_EX ${CMAKE_CURRENT_SOURCE_DIR}/shaders/*.glsl)

# library
add_library(${PROJECT_NAME}
    ${CondorEngine_HEADERS} 
    ${CondorEngine_SOURCES}
    ${CondorEngine_SHADERS}
    ${CondorEngine_SHADER_EX}
    ${CondorEngine_THIRD_PARTY_DIR}/stb/stb_image.h
)
target_compile_definitions(${PROJECT_NAME} PRIVATE CondorEngine_EXPORTS)
target_include_directories(${PROJECT_NAME} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)
target_include_directories(${PROJECT_NAME} PUBLIC ${CondorEngine_THIRD_PARTY_DIR}/stb)
set_property(TARGET ${PROJECT_NAME} PROPERTY
    MSVC_RUNTIME_LIBRARY "MultiThreadedDLL"
)

# dependencies
target_link_libraries(${PROJECT_NAME} PUBLIC assimp)
target_link_libraries(${PROJECT_NAME} PUBLIC glad)
target_link_libraries(${PROJECT_NAME} PUBLIC glfw)
target_link_libraries(${PROJECT_NAME} PUBLIC glm::glm)
target_link_libraries(${PROJECT_NAME} PUBLIC imgui)
target_link_libraries(${PROJECT_NAME} PUBLIC OpenGL::GL)
add_dependencies(${PROJECT_NAME} CondorEngine_CopyResources)
add_dependencies(${PROJECT_NAME} CondorEngine_ProcessShaders)

# memory verification (ASan)
if (CMAKE_CXX_COMPILER_ID MATCHES "Clang|GNU")
    add_compile_options(-fsanitize=address -g -O1)
    add_link_options(-fsanitize=address)
elseif(MSVC)
    add_compile_options(/fsanitize=address /Zi)
endif()

# folder
if (NOT CondorEngine_IS_ROOT_PROJECT)
    set_target_properties(${PROJECT_NAME} PROPERTIES FOLDER "Engine")
endif()