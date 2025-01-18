#pragma once
#include "CondorEngine/pch.h"
// third party
#include "CondorEngine/renderer.h"
#include "CondorEngine/sceneobject.h"
#include "CondorEngine/components/mesh.h"
#include "CondorEngine/components/rigidbody.h"
#include "CondorEngine/components/collider.h"
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
	/// @brief SceneObject with primitive mesh.
	class DllExport Primitive : public SceneObject
	{
	public:
		/// @brief Class constructor.
		/// @param type Mesh type.
		/// @param material Mesh material.
		Primitive(PrimitiveType type, Material *material);
		/// @brief Class constructor.
		/// @param type Mesh type.
		Primitive(PrimitiveType type);
		/// @brief Primitive mesh component.
		Mesh *mesh;
		/// @brief Primitive rigidbody component.
		Rigidbody *rigidbody;
		/// @brief Primitive collider component.
		Collider *collider;
		/// @brief Make a simple primitive cube.
		/// @return Simple primitive cube mesh.
		static Mesh *MakeSimpleCube();
		/// @brief Make a primitive cube.
		/// @return Primitive cube mesh.
		static Mesh *MakeCube();
		/// @brief Make a primitive sphere mesh.
		/// @return Primitive sphere mesh.
		static Mesh *MakeSphere();
		/// @brief Make a primitive cylinder mesh.
		/// @return Primitive cylinder mesh.
		static Mesh *MakeCylinder();
		/// @brief Make a primitive plane mesh.
		/// @return Primitive plane mesh.
		static Mesh *MakePlane();
	};
}
