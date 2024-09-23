#pragma once
#include "../renderer.h"
#include "../core.h"
#include "../components/mesh.h"
// std
#include <vector>
// third party
#include "glew/glew.h"

namespace CondorEngine {
	/// @brief Primitive mesh type.
	enum PrimitiveType {
		SimpleCube,
		Cube
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
	private:
		/// @brief Make a simple primitive cube.
		/// @return Simple primitive cube mesh.
		static Mesh* MakeSimpleCube();
		/// @brief Make a primitive cube.
		/// @return Primitive cube mesh.
		static Mesh* MakeCube();
	};
}
