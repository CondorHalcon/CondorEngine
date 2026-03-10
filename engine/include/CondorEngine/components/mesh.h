#pragma once
#include "CondorEngine/pch.h"
// internal
#include "CondorEngine/rendering/renderer.h"
#include "CondorEngine/component.h"
#include "CondorEngine/material.h"
#include "CondorEngine/resourcemanager.h"
// third party
#include <glm/glm.hpp>

namespace CondorEngine
{
	/// @brief Mesh component class.
	class DllExport Mesh : public Component
	{
		REFLECT_CLASS(CondorEngine::Mesh, Component)
	public:
		Mesh(Resource<MeshData>* meshData, Material* material);
		Mesh(Resource<MeshData>* meshData);
		Mesh();
		/// @brief Class deconstructor.
		~Mesh();

	public:
		/// @brief Mesh data.
		REFLECT_FIELD(Resource<MeshData>*, meshData)
		/// @brief Render shader for the mesh.
		REFLECT_FIELD(Material*, material)
		/// @brief Register mesh for rendering this frame.
		void LateUpdate() override;
	};
}
