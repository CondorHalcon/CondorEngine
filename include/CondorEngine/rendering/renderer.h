#pragma once
#include "CondorEngine/pch.h"
// internal
#include "CondorEngine/math.hpp"
// std
#include <vector>
#include <string>

namespace CondorEngine
{
	class Mesh;
	class Light;
	class Material;

#pragma region Struct Definitions
	/// @brief Mesh vertex struct
	struct DllExport Vertex
	{
		/// @brief Vertex position
		Vector4 pos;
		/// @brief Vertex color
		Color col;
		/// @brief UV
		Vector2 uv;
		/// @brief Vertex normal
		Vector3 normal;
	};

	/// @brief Mesh data.
	struct DllExport MeshData
	{
		/// @brief vertex array object
		GLuint vao;
		/// @brief vertex buffer object
		GLuint vbo;
		/// @brief index buffer object
		GLuint ibo;
		/// @brief index count
		GLuint size;

		/// @brief Make a mesh in OpenGL.
		/// @param verts Mesh vertices.
		/// @param vertCount Mesh vertex count.
		/// @param indices Mesh indices.
		/// @param indexCount Mesh index count.
		static MeshData MakeMesh(const Vertex* const verts, GLsizei vertCount, const GLuint* indices, GLsizei indexCount);
		/// @brief Make a mesh in OpenGL.
		/// @param verts Mesh vertices.
		/// @param indices Mesh indices.
		static MeshData MakeMesh(const std::vector<Vertex> verts, const std::vector<GLuint> indices);
		/// @brief Load a mesh from an `.obj` file.
		/// @param filename Mesh file path.
		/// @return Loaded mesh.
		static MeshData LoadMesh(const char* filepath);
		/// @brief Unload a mesh from OpenGL.
		/// @param mesh Mesh to unload.
		static void FreeMesh(MeshData& mesh);
	};

	/// @brief Shader reference.
	struct DllExport Shader
	{
		/// @brief OpenGL shader program.
		GLuint program;

		/// @brief Compile a shader in OpenGl.
		/// @param vertShader Vertex shader.
		/// @param fragShader Fragment shader.
		/// @return Compiled shader.
		static Shader MakeShader(const char* vertShader, const char* fragShader);
		/// @brief Compile a shader in OpenGl.
		/// @param vertShader Vertex shader.
		/// @param fragShader Fragment shader.
		/// @return Compiled shader.
		static Shader MakeShader(const std::string& vertShader, const std::string& fragShader);
		/// @brief Load and compile a shader in OpenGl.
		/// @param vertShader Vertex shader file path.
		/// @param fragShader Fragment shader file path.
		/// @return Compiled shader.
		static Shader LoadShader(const char* vertPath, const char* fragPath);
		/// @brief Unload shader from OpenGL.
		/// @param shader Shader to unload.
		static void FreeShader(Shader& shader);
	};

	/// @brief OpenGL texture & metadata.
	struct DllExport Texture
	{
		/// @brief OpenGL texture name
		GLuint handle;
		unsigned width;
		unsigned height;
		unsigned channels;

		/// @brief Make a texture in OpenGL.
		/// @param width Texture width.
		/// @param height Texture height.
		/// @param channels Texture color channels.
		/// @param pixels Pixel data.
		/// @return
		static Texture MakeTexture(unsigned width, unsigned height, unsigned channels, const unsigned char* pixels);
		/// @brief Load a texture into OpenGL from a file.
		/// @param imagePath Texture file path.
		/// @return
		static Texture LoadTexture(const char* imagePath);
		/// @brief Unload a texture from OpenGL.
		/// @param tex Texture to unload.
		static void FreeTexture(Texture& tex);
	};

	/// @brief Directional light struct.
	struct DllExport DirectionalLight
	{
		/// @brief Light color.
		ColorRGB color;
		/// @brief Light direction.
		Vector3 direction;

		DirectionalLight(ColorRGB col, Vector3 dir);
		DirectionalLight();
	};
#pragma endregion

	namespace Rendering
	{
		class RenderFeature;

		/// @brief Render handler class.
		class DllExport Renderer
		{
		protected:
			Renderer();
			~Renderer();
			static Renderer* instance;

		public:
			/// @brief Meshes to render this frame.
			static std::vector<Mesh*> meshes;
			/// @brief Lights to render this frame.
			static std::vector<Light*> lights;

			std::vector<RenderFeature*> featuresMain;

			static Renderer* Instance();

			/// @brief Initialize renderer.
			virtual void init();
			/// @brief Render registered meshes.
			virtual void Render();
		};
	}
}
