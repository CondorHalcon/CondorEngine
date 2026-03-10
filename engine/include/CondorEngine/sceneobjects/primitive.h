#pragma once
#include "CondorEngine/pch.h"
// third party
#include "CondorEngine/rendering/renderer.h"
#include "CondorEngine/sceneobject.h"
#include "CondorEngine/components/mesh.h"
#include "CondorEngine/components/rigidbody.h"
#include "CondorEngine/components/collider.h"
#include "CondorEngine/resourcemanager.h"
// std
#include <vector>
// third party
// #include "glew.h"

namespace CondorEngine
{
	/// @brief Primitive mesh type.
	enum DllExport PrimitiveType
	{
		SimpleCubeMesh,
		CubeMesh,
		PlaneMesh,
		SphereMesh,
		CylinderMesh
	};

	REFLECT_ENUM_BEGIN(PrimitiveType)
		REFLECT_ENUM_VALUE(PrimitiveType, SimpleCubeMesh)
		REFLECT_ENUM_VALUE(PrimitiveType, CubeMesh)
		REFLECT_ENUM_VALUE(PrimitiveType, PlaneMesh)
		REFLECT_ENUM_VALUE(PrimitiveType, SphereMesh)
		REFLECT_ENUM_VALUE(PrimitiveType, CylinderMesh)
		REFLECT_ENUM_END(PrimitiveType)

	/// @brief SceneObject with primitive mesh.
	class DllExport Primitive : public SceneObject
	{
		REFLECT_CLASS(CondorEngine::Primitive, SceneObject)
	public:
		static Resource<MeshData>* simpleCubeMesh;
		static Resource<MeshData>* cubeMesh;
		static Resource<MeshData>* planeMesh;
		static Resource<MeshData>* sphereMesh;
		static Resource<MeshData>* cylinderMesh;
		
		/// @brief Class constructor.
		/// @param type Mesh type.
		/// @param material Mesh material.
		Primitive(PrimitiveType type, Material *material);
		/// @brief Class constructor.
		/// @param type Mesh type.
		Primitive(PrimitiveType type);
		/// @brief Default class constructor.
		Primitive();

		/// @brief Primitive mesh component.
		REFLECT_FIELD(Mesh*, mesh)
		/// @brief Primitive rigidbody component.
		REFLECT_FIELD(Rigidbody*, rigidbody)
		/// @brief Primitive collider component.
		REFLECT_FIELD(Collider*, collider)
		/// @brief Make a simple primitive cube.
		/// @return Simple primitive cube mesh.
		static MeshData MakeSimpleCube();
		/// @brief Make a primitive cube.
		/// @return Primitive cube mesh.
		static MeshData MakeCube();
		/// @brief Make a primitive sphere mesh.
		/// @return Primitive sphere mesh.
		static MeshData MakeSphere();
		/// @brief Make a primitive cylinder mesh.
		/// @return Primitive cylinder mesh.
		static MeshData MakeCylinder();
		/// @brief Make a primitive plane mesh.
		/// @return Primitive plane mesh.
		static MeshData MakePlane();
	};
}
