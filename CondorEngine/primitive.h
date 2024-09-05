#pragma once
#include "renderer.h"
#include "core.h"
// std
#include <vector>
// third party
#include "glew/glew.h"

namespace CondorEngine {
	enum PrimitiveType {
		SimpleCube,
		Cube
	};
	class Primitive : public SceneObject
	{
	public:
		Primitive(PrimitiveType type);
		Mesh* mesh;
	private:
		static Mesh MakeSimpleCube();
		static Mesh MakeCube();
	};
}
