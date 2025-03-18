#pragma once
#include "CondorEngine/pch.h"
// internal
#include "CondorEngine/renderer.h"
#include "CondorEngine/component.h"
#include "CondorEngine/material.h"
// third party
#include <glm/glm.hpp>

namespace CondorEngine
{
	/// @brief Mesh component class.
	class DllExport Mesh : public Component
	{
	public:
		Mesh(MeshData meshData, Material* material);
		Mesh(MeshData meshData);
		/// @brief Class deconstructor.
		~Mesh();

	public:
		/// @brief Mesh data.
		MeshData data;
		/// @brief Render shader for the mesh.
		Material *material;
		/// @brief Register mesh for rendering this frame.
		void LateUpdate() override;
		/// @brief Render mesh.
		virtual void Render();
	};
}
