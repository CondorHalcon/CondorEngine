#pragma once
#include "CondorEngine/pch.h"
// internal
#include "CondorEngine/math.hpp"
#include "CondorEngine/object.h"
#include "CondorEngine/rendering/renderfeature.h"
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
		REFLECT_STRUCT(CondorEngine::Vertex)
		Vertex(Vector4 position, Color color, Vector2 uv, Vector3 normal);
		Vertex();

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
		REFLECT_STRUCT(CondorEngine::MeshData)
		
		MeshData(GLuint vao, GLuint vbo, GLuint ibo, GLuint size);
		MeshData();

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
		REFLECT_STRUCT(CondorEngine::Shader)
		
		Shader(GLuint program);
		Shader();
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
		REFLECT_STRUCT(CondorEngine::Texture)
		/// @brief OpenGL texture name
		GLuint handle;
		unsigned width;
		unsigned height;
		unsigned channels;

		Texture(GLuint handle, unsigned width, unsigned height, unsigned channels);
		Texture();

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
		REFLECT_STRUCT(CondorEngine::DirectionalLight)
		/// @brief Light color.
		REFLECT_FIELD(ColorRGB, color)
		/// @brief Light direction.
		REFLECT_FIELD(Vector3, direction)

		DirectionalLight(ColorRGB col, Vector3 dir);
		DirectionalLight();
	};
#pragma endregion

#pragma region Renderer

	namespace Rendering
	{
		/// @brief Render handler class.
		class DllExport Renderer : public Object
		{
			REFLECT_CLASS(CondorEngine::Rendering::Renderer, Object)
		protected:
			Renderer();
			~Renderer();
			static inline Renderer* instance = nullptr;

		public:
			static Renderer* Instance() {
				if (instance == nullptr) {
					instance = new Renderer();
				}
				return instance;
			}

			/// @brief Meshes to render this frame.
			static std::vector<Mesh*> meshes;
			/// @brief Lights to render this frame.
			static std::vector<Light*> lights;

			/// @brief Color to clear the screen buffer.
			REFLECT_FIELD(ColorRGB, clearColorRGB)
			REFLECT_FIELD(std::vector<RenderFeature*>, features)

			/// @brief Initialize renderer.
			/// @note When overriding this method, it is recommended to call the base method `Renderer::init()` first then add to it.
			virtual void init();

			/// @brief Render registered meshes.
			/// @note Be VERY careful when overriding this method; the order it does things affects how other classes work.
			virtual void Render();

		protected:
			void ResetScreen();

		public:

			// TODO turn into a proper abstraction layer
#pragma region Render

			static void viewport(GLint x, GLint y, GLsizei width, GLsizei height);
			static void clearColor(ColorRGB color);
			static void clear(GLbitfield mask);
			static void drawElements(GLenum mode, GLsizei count, GLenum type, const void* indices);

#pragma endregion

#pragma region Texture

			static void genTextures(GLsizei n, GLuint* textures);
			static void deleteTextures(GLsizei n, const GLuint* textures);
			static void bindTexture(GLenum target, GLuint texture);
			static void texImage2D(GLenum target, GLint level, GLint internalformat, GLsizei width, GLsizei height, GLint border, GLenum format, GLenum type, const void* data);
			static void texParameteri(GLenum target, GLenum pname, GLint param);

#pragma endregion

#pragma region Renderbuffer

			static void genRenderbuffers(GLsizei n, GLuint* renderbuffers);
			static void deleteRenderbuffers(GLsizei n, GLuint* renderbuffers);
			static void bindRenderbuffer(GLenum target, GLuint renderbuffer);
			static void renderbufferStorage(GLenum target, GLenum internalformat, GLsizei width, GLsizei height);
			static void framebufferRenderbuffer(GLenum target, GLenum attachment, GLenum renderbuffertarget, GLuint renderbuffer);
			static GLenum checkFramebufferStatus(GLenum target);

#pragma endregion

#pragma region Framebuffers / Render Targets

			static void genFramebuffers(GLsizei n, GLuint* framebuffers);
			static void deleteFramebuffers(GLsizei n, GLuint* framebuffers);
			static void bindFramebuffer(GLenum target, GLuint framebuffer);
			static void framebufferTexture2D(GLenum target, GLenum attachment, GLenum texTarget, GLuint texture, GLint level);
#pragma endregion

#pragma region Shaders

			static void useProgram(GLuint program);

#pragma endregion

#pragma region Buffers(Vertex / Index / Uniform)

			static void bindVertexArray(GLuint array);

#pragma endregion
		};
	}

#pragma endregion
}
