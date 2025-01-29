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
		/// @brief Class constructor.
		/// @param verts Mesh vertices.
		/// @param vertCount Mesh vertex count.
		/// @param indices Mesh indices.
		/// @param indexCount Mesh index count.
		Mesh(const Vertex *const verts, GLsizei vertCount, const GLuint *indices, GLsizei indexCount);
		/// @brief Class constructor.
		/// @param verts Mesh vertices.
		/// @param indices Mesh indices.
		Mesh(const std::vector<Vertex> verts, const std::vector<GLuint> indices);
		/// @brief Load a mesh from and `.obj` file.
		/// @param filename Mesh file path.
		/// @param material Material to assign to the mesh.
		/// @return Loaded mesh.
		static Mesh *LoadMeshFromFile(const char *filename, Material *material);
		/// @brief Load a mesh from and `.obj` file.
		/// @param filename Mesh file path.
		/// @return Loaded mesh.
		static Mesh *LoadMeshFromFile(const char *filename);
		/// @brief Class deconstructor.
		~Mesh();

	private:
		/// @brief vertex array object
		GLuint vao;
		/// @brief vertex buffer object
		GLuint vbo;
		/// @brief index buffer object
		GLuint ibo;
		/// @brief index count
		GLuint size;

	public:
		/// @brief Render shader for the mesh.
		Material *material;
		/// @brief Register mesh for rendering this frame.
		void LateUpdate() override;
		/// @brief Render mesh.
		virtual void Render();
	};
}
