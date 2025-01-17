# Install script for directory: C:/Users/s239056/Downloads/assimp-5.4.3/code

# Set the install prefix
if(NOT DEFINED CMAKE_INSTALL_PREFIX)
  set(CMAKE_INSTALL_PREFIX "C:/Users/s239056/Downloads/assimp-5.4.3/out/install/x64-Debug")
endif()
string(REGEX REPLACE "/$" "" CMAKE_INSTALL_PREFIX "${CMAKE_INSTALL_PREFIX}")

# Set the install configuration name.
if(NOT DEFINED CMAKE_INSTALL_CONFIG_NAME)
  if(BUILD_TYPE)
    string(REGEX REPLACE "^[^A-Za-z0-9_]+" ""
           CMAKE_INSTALL_CONFIG_NAME "${BUILD_TYPE}")
  else()
    set(CMAKE_INSTALL_CONFIG_NAME "Debug")
  endif()
  message(STATUS "Install configuration: \"${CMAKE_INSTALL_CONFIG_NAME}\"")
endif()

# Set the component getting installed.
if(NOT CMAKE_INSTALL_COMPONENT)
  if(COMPONENT)
    message(STATUS "Install component: \"${COMPONENT}\"")
    set(CMAKE_INSTALL_COMPONENT "${COMPONENT}")
  else()
    set(CMAKE_INSTALL_COMPONENT)
  endif()
endif()

# Is this installation the result of a crosscompile?
if(NOT DEFINED CMAKE_CROSSCOMPILING)
  set(CMAKE_CROSSCOMPILING "FALSE")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "libassimp5.4.3-dev" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib" TYPE STATIC_LIBRARY OPTIONAL FILES "C:/Users/s239056/Downloads/assimp-5.4.3/out/build/x64-Debug/lib/assimp-vc143-mtd.lib")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "libassimp5.4.3" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/bin" TYPE SHARED_LIBRARY FILES "C:/Users/s239056/Downloads/assimp-5.4.3/out/build/x64-Debug/bin/assimp-vc143-mtd.dll")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "assimp-dev" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/assimp" TYPE FILE FILES
    "C:/Users/s239056/Downloads/assimp-5.4.3/code/../include/assimp/anim.h"
    "C:/Users/s239056/Downloads/assimp-5.4.3/code/../include/assimp/aabb.h"
    "C:/Users/s239056/Downloads/assimp-5.4.3/code/../include/assimp/ai_assert.h"
    "C:/Users/s239056/Downloads/assimp-5.4.3/code/../include/assimp/camera.h"
    "C:/Users/s239056/Downloads/assimp-5.4.3/code/../include/assimp/color4.h"
    "C:/Users/s239056/Downloads/assimp-5.4.3/code/../include/assimp/color4.inl"
    "C:/Users/s239056/Downloads/assimp-5.4.3/out/build/x64-Debug/code/../include/assimp/config.h"
    "C:/Users/s239056/Downloads/assimp-5.4.3/code/../include/assimp/ColladaMetaData.h"
    "C:/Users/s239056/Downloads/assimp-5.4.3/code/../include/assimp/commonMetaData.h"
    "C:/Users/s239056/Downloads/assimp-5.4.3/code/../include/assimp/defs.h"
    "C:/Users/s239056/Downloads/assimp-5.4.3/code/../include/assimp/cfileio.h"
    "C:/Users/s239056/Downloads/assimp-5.4.3/code/../include/assimp/light.h"
    "C:/Users/s239056/Downloads/assimp-5.4.3/code/../include/assimp/material.h"
    "C:/Users/s239056/Downloads/assimp-5.4.3/code/../include/assimp/material.inl"
    "C:/Users/s239056/Downloads/assimp-5.4.3/code/../include/assimp/matrix3x3.h"
    "C:/Users/s239056/Downloads/assimp-5.4.3/code/../include/assimp/matrix3x3.inl"
    "C:/Users/s239056/Downloads/assimp-5.4.3/code/../include/assimp/matrix4x4.h"
    "C:/Users/s239056/Downloads/assimp-5.4.3/code/../include/assimp/matrix4x4.inl"
    "C:/Users/s239056/Downloads/assimp-5.4.3/code/../include/assimp/mesh.h"
    "C:/Users/s239056/Downloads/assimp-5.4.3/code/../include/assimp/ObjMaterial.h"
    "C:/Users/s239056/Downloads/assimp-5.4.3/code/../include/assimp/pbrmaterial.h"
    "C:/Users/s239056/Downloads/assimp-5.4.3/code/../include/assimp/GltfMaterial.h"
    "C:/Users/s239056/Downloads/assimp-5.4.3/code/../include/assimp/postprocess.h"
    "C:/Users/s239056/Downloads/assimp-5.4.3/code/../include/assimp/quaternion.h"
    "C:/Users/s239056/Downloads/assimp-5.4.3/code/../include/assimp/quaternion.inl"
    "C:/Users/s239056/Downloads/assimp-5.4.3/code/../include/assimp/scene.h"
    "C:/Users/s239056/Downloads/assimp-5.4.3/code/../include/assimp/metadata.h"
    "C:/Users/s239056/Downloads/assimp-5.4.3/code/../include/assimp/texture.h"
    "C:/Users/s239056/Downloads/assimp-5.4.3/code/../include/assimp/types.h"
    "C:/Users/s239056/Downloads/assimp-5.4.3/code/../include/assimp/vector2.h"
    "C:/Users/s239056/Downloads/assimp-5.4.3/code/../include/assimp/vector2.inl"
    "C:/Users/s239056/Downloads/assimp-5.4.3/code/../include/assimp/vector3.h"
    "C:/Users/s239056/Downloads/assimp-5.4.3/code/../include/assimp/vector3.inl"
    "C:/Users/s239056/Downloads/assimp-5.4.3/code/../include/assimp/version.h"
    "C:/Users/s239056/Downloads/assimp-5.4.3/code/../include/assimp/cimport.h"
    "C:/Users/s239056/Downloads/assimp-5.4.3/code/../include/assimp/AssertHandler.h"
    "C:/Users/s239056/Downloads/assimp-5.4.3/code/../include/assimp/importerdesc.h"
    "C:/Users/s239056/Downloads/assimp-5.4.3/code/../include/assimp/Importer.hpp"
    "C:/Users/s239056/Downloads/assimp-5.4.3/code/../include/assimp/DefaultLogger.hpp"
    "C:/Users/s239056/Downloads/assimp-5.4.3/code/../include/assimp/ProgressHandler.hpp"
    "C:/Users/s239056/Downloads/assimp-5.4.3/code/../include/assimp/IOStream.hpp"
    "C:/Users/s239056/Downloads/assimp-5.4.3/code/../include/assimp/IOSystem.hpp"
    "C:/Users/s239056/Downloads/assimp-5.4.3/code/../include/assimp/Logger.hpp"
    "C:/Users/s239056/Downloads/assimp-5.4.3/code/../include/assimp/LogStream.hpp"
    "C:/Users/s239056/Downloads/assimp-5.4.3/code/../include/assimp/NullLogger.hpp"
    "C:/Users/s239056/Downloads/assimp-5.4.3/code/../include/assimp/cexport.h"
    "C:/Users/s239056/Downloads/assimp-5.4.3/code/../include/assimp/Exporter.hpp"
    "C:/Users/s239056/Downloads/assimp-5.4.3/code/../include/assimp/DefaultIOStream.h"
    "C:/Users/s239056/Downloads/assimp-5.4.3/code/../include/assimp/DefaultIOSystem.h"
    "C:/Users/s239056/Downloads/assimp-5.4.3/code/../include/assimp/ZipArchiveIOSystem.h"
    "C:/Users/s239056/Downloads/assimp-5.4.3/code/../include/assimp/SceneCombiner.h"
    "C:/Users/s239056/Downloads/assimp-5.4.3/code/../include/assimp/fast_atof.h"
    "C:/Users/s239056/Downloads/assimp-5.4.3/code/../include/assimp/qnan.h"
    "C:/Users/s239056/Downloads/assimp-5.4.3/code/../include/assimp/BaseImporter.h"
    "C:/Users/s239056/Downloads/assimp-5.4.3/code/../include/assimp/Hash.h"
    "C:/Users/s239056/Downloads/assimp-5.4.3/code/../include/assimp/MemoryIOWrapper.h"
    "C:/Users/s239056/Downloads/assimp-5.4.3/code/../include/assimp/ParsingUtils.h"
    "C:/Users/s239056/Downloads/assimp-5.4.3/code/../include/assimp/StreamReader.h"
    "C:/Users/s239056/Downloads/assimp-5.4.3/code/../include/assimp/StreamWriter.h"
    "C:/Users/s239056/Downloads/assimp-5.4.3/code/../include/assimp/StringComparison.h"
    "C:/Users/s239056/Downloads/assimp-5.4.3/code/../include/assimp/StringUtils.h"
    "C:/Users/s239056/Downloads/assimp-5.4.3/code/../include/assimp/SGSpatialSort.h"
    "C:/Users/s239056/Downloads/assimp-5.4.3/code/../include/assimp/GenericProperty.h"
    "C:/Users/s239056/Downloads/assimp-5.4.3/code/../include/assimp/SpatialSort.h"
    "C:/Users/s239056/Downloads/assimp-5.4.3/code/../include/assimp/SkeletonMeshBuilder.h"
    "C:/Users/s239056/Downloads/assimp-5.4.3/code/../include/assimp/SmallVector.h"
    "C:/Users/s239056/Downloads/assimp-5.4.3/code/../include/assimp/SmoothingGroups.h"
    "C:/Users/s239056/Downloads/assimp-5.4.3/code/../include/assimp/SmoothingGroups.inl"
    "C:/Users/s239056/Downloads/assimp-5.4.3/code/../include/assimp/StandardShapes.h"
    "C:/Users/s239056/Downloads/assimp-5.4.3/code/../include/assimp/RemoveComments.h"
    "C:/Users/s239056/Downloads/assimp-5.4.3/code/../include/assimp/Subdivision.h"
    "C:/Users/s239056/Downloads/assimp-5.4.3/code/../include/assimp/Vertex.h"
    "C:/Users/s239056/Downloads/assimp-5.4.3/code/../include/assimp/LineSplitter.h"
    "C:/Users/s239056/Downloads/assimp-5.4.3/code/../include/assimp/TinyFormatter.h"
    "C:/Users/s239056/Downloads/assimp-5.4.3/code/../include/assimp/Profiler.h"
    "C:/Users/s239056/Downloads/assimp-5.4.3/code/../include/assimp/LogAux.h"
    "C:/Users/s239056/Downloads/assimp-5.4.3/code/../include/assimp/Bitmap.h"
    "C:/Users/s239056/Downloads/assimp-5.4.3/code/../include/assimp/XMLTools.h"
    "C:/Users/s239056/Downloads/assimp-5.4.3/code/../include/assimp/IOStreamBuffer.h"
    "C:/Users/s239056/Downloads/assimp-5.4.3/code/../include/assimp/CreateAnimMesh.h"
    "C:/Users/s239056/Downloads/assimp-5.4.3/code/../include/assimp/XmlParser.h"
    "C:/Users/s239056/Downloads/assimp-5.4.3/code/../include/assimp/BlobIOSystem.h"
    "C:/Users/s239056/Downloads/assimp-5.4.3/code/../include/assimp/MathFunctions.h"
    "C:/Users/s239056/Downloads/assimp-5.4.3/code/../include/assimp/Exceptional.h"
    "C:/Users/s239056/Downloads/assimp-5.4.3/code/../include/assimp/ByteSwapper.h"
    "C:/Users/s239056/Downloads/assimp-5.4.3/code/../include/assimp/Base64.hpp"
    )
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "assimp-dev" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/assimp/Compiler" TYPE FILE FILES
    "C:/Users/s239056/Downloads/assimp-5.4.3/code/../include/assimp/Compiler/pushpack1.h"
    "C:/Users/s239056/Downloads/assimp-5.4.3/code/../include/assimp/Compiler/poppack1.h"
    "C:/Users/s239056/Downloads/assimp-5.4.3/code/../include/assimp/Compiler/pstdint.h"
    )
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib" TYPE FILE FILES "C:/Users/s239056/Downloads/assimp-5.4.3/out/build/x64-Debug/bin/assimp-vc143-mtd.pdb")
endif()

