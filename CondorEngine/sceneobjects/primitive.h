#pragma once
// third party
#include "../renderer.h"
#include "../sceneobject.h"
#include "../components/mesh.h"
#include "../components/rigidbody.h"
#include "../components/collider.h"
// std
#include <vector>
// third party
#include "glew/glew.h"

namespace CondorEngine {
	/// @brief Primitive mesh type.
	enum PrimitiveType {
		SimpleCubeMesh,
		CubeMesh,
		PlaneMesh,
		SphereMesh,
		CylinderMesh
	};
	/// @brief SceneObject with primitive mesh.
	class Primitive : public SceneObject
	{
	public:
		/// @brief Class constructor.
		/// @param type Mesh type.
		/// @param material Mesh material.
		Primitive(PrimitiveType type, Material* material);
		/// @brief Class constructor.
		/// @param type Mesh type.
		Primitive(PrimitiveType type);
		/// @brief Primitive mesh component.
		Mesh* mesh;
		/// @brief Primitive rigidbody component.
		Rigidbody *rigidbody;
		/// @brief Primitive collider component.
		Collider* collider;
	private:
		/// @brief Make a simple primitive cube.
		/// @return Simple primitive cube mesh.
		static Mesh* MakeSimpleCube();
		/// @brief Make a primitive cube.
		/// @return Primitive cube mesh.
		static Mesh* MakeCube();
		/// @brief Make a primitive sphere mesh.
		/// @return Primitive sphere mesh.
		static Mesh* MakeSphere();
		/// @brief Make a primitive cylinder mesh.
		/// @return Primitive cylinder mesh.
		static Mesh* MakeCylinder();
		/// @brief Make a primitive plane mesh.
		/// @return Primitive plane mesh.
		static Mesh* MakePlane();
	};
}
