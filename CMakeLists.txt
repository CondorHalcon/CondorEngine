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

# global output directories
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


# subdirectories
add_subdirectory(tools)
set(SHADER_PREPROCESSOR ${CMAKE_BINARY_DIR}/tools/bin/$<CONFIG>/CondorEngine_ShaderPreprocessor)
add_subdirectory(engine)
add_subdirectory(editor)
add_subdirectory(samples)
