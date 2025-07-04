#--------------------------------------------------------------------
# Project: CondorEngine
#--------------------------------------------------------------------
cmake_minimum_required(VERSION 3.13...3.31)
project(CondorEngine VERSION 0.2.0 LANGUAGES CXX C)
set_property(GLOBAL PROPERTY USE_FOLDERS ON)
message(STATUS "${PROJECT_NAME} :: Configuring ${PROJECT_NAME} v${PROJECT_VERSION}...")

# source and root directories 
set(CondorEngine_IS_ROOT_PROJECT OFF)
set(CondorEngine_SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR})
if (${CMAKE_SOURCE_DIR} STREQUAL ${CMAKE_CURRENT_SOURCE_DIR})
    set(CondorEngine_IS_ROOT_PROJECT ON)
endif()

# cpp standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# output directories
set(CondorEngine_OS_BIT 32)
if(CMAKE_SIZEOF_VOID_P EQUAL 8)
    set(CondorEngine_OS_BIT 64)
endif()
set(CondorEngine_FULL_OUTPUT_DIR ${CMAKE_RUNTIME_OUTPUT_DIRECTORY})
if (CondorEngine_IS_ROOT_PROJECT)
    set(CondorEngine_FULL_OUTPUT_DIR ${CMAKE_CURRENT_SOURCE_DIR}/bin/${CMAKE_SYSTEM_NAME}/x${CondorEngine_OS_BIT})
    set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CondorEngine_FULL_OUTPUT_DIR}/lib)
    set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CondorEngine_FULL_OUTPUT_DIR})
    set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CondorEngine_FULL_OUTPUT_DIR})
endif()

#--------------------------------------------------------------------
# Third Party Libraries
#--------------------------------------------------------------------
message(STATUS "${PROJECT_NAME} :: Configuring third party libraries")
set(CondorEngine_THIRD_PARTY_DIR ${CMAKE_CURRENT_SOURCE_DIR}/thirdparty)

# assimp
add_subdirectory(${CondorEngine_THIRD_PARTY_DIR}/assimp)
set_target_properties(assimp PROPERTIES FOLDER "EngineLibs")
set_target_properties(UpdateAssimpLibsDebugSymbolsAndDLLs PROPERTIES FOLDER "EngineLibs/assimp_utils")
set_target_properties(uninstall PROPERTIES FOLDER "EngineLibs/assimp_utils")
set_target_properties(unit PROPERTIES FOLDER "EngineLibs/assimp_utils")
set_target_properties(zlibstatic PROPERTIES FOLDER "EngineLibs/assimp_utils")
# glew
message(STATUS "GLEW :: Importing lib")
add_library(glew STATIC IMPORTED)
set (glew_IMPORT_DIR ${CondorEngine_THIRD_PARTY_DIR}/glew/lib/Win32)
if (CondorEngine_OS_BIT EQUAL 64)
    set (glew_IMPORT_DIR ${CondorEngine_THIRD_PARTY_DIR}/glew/lib/x64)
endif()
set_target_properties(glew PROPERTIES
    IMPORTED_LOCATION ${glew_IMPORT_DIR}/glew32s.lib
)
target_include_directories(glew INTERFACE ${CondorEngine_THIRD_PARTY_DIR}/glew)
set_target_properties(glew PROPERTIES FOLDER "EngineLibs")

# glfw
set(GLFW_LIBRARY_TYPE STATIC)
add_subdirectory(${CondorEngine_THIRD_PARTY_DIR}/glfw)
set_target_properties(glfw PROPERTIES FOLDER "EngineLibs")
if (docs)
    set_target_properties(docs PROPERTIES FOLDER "EngineLibs/glfw_utils")
endif()
set_target_properties(update_mappings PROPERTIES FOLDER "EngineLibs/glfw_utils")
# glm
add_subdirectory(${CondorEngine_THIRD_PARTY_DIR}/glm)
set_target_properties(glm PROPERTIES FOLDER "EngineLibs")
# OpenGL
find_package(OpenGL REQUIRED)

#--------------------------------------------------------------------
# Tools Subdirectory
#--------------------------------------------------------------------
add_subdirectory(tools)
set(SHADER_PREPROCESSOR ${CMAKE_BINARY_DIR}/tools/bin/$<CONFIG>/CondorEngine_ShaderPreprocessor)

#--------------------------------------------------------------------
# MAIN: CondorEngine
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

# dependencies
target_link_libraries(${PROJECT_NAME} PUBLIC assimp)
target_link_libraries(${PROJECT_NAME} PUBLIC glew)
target_link_libraries(${PROJECT_NAME} PUBLIC glfw)
target_link_libraries(${PROJECT_NAME} PUBLIC glm::glm)
target_link_libraries(${PROJECT_NAME} PUBLIC OpenGL::GL)
add_dependencies(${PROJECT_NAME} CondorEngine_CopyResources)
add_dependencies(${PROJECT_NAME} CondorEngine_ProcessShaders)

# folder
if (NOT CondorEngine_IS_ROOT_PROJECT)
    set_target_properties(${PROJECT_NAME} PROPERTIES FOLDER "Engine")
endif()

#--------------------------------------------------------------------
# Demo: CondorEngine_DemoGame Subdirectory
#--------------------------------------------------------------------
add_subdirectory(demo)

#--------------------------------------------------------------------
# Demo: CondorEngine_Samples Subdirectory
#--------------------------------------------------------------------
add_subdirectory(samples)
