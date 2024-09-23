#pragma once
#include "core.h"

// third party
#include "glew/glew.h"
// std
#include <vector> // for the daring
#include <string>
using std::string;

namespace CondorEngine {

#pragma region Struct Definitions
	/// @brief Mesh vertex struct
	struct Vertex {
		/// @brief Vertex position
		Vector4 pos;
		/// @brief Vertex color
		Color col;
		/// @brief UV
		Vector2 uv;
		/// @brief Vertex normal
		Vector3 normal;
	};

	/// @brief Shader reference.
	struct Shader
	{
		/// @brief OpenGL shader program.
		GLuint program;

		/// @brief Compile a shader in OpenGl.
		/// @param vertShader Vertex shader.
		/// @param fragShader Fragment shader.
		/// @return Compiled shader.
		static Shader* MakeShader(const char* vertShader, const char* fragShader);
		/// @brief Compile a shader in OpenGl.
		/// @param vertShader Vertex shader.
		/// @param fragShader Fragment shader.
		/// @return Compiled shader.
		static Shader* MakeShader(const string& vertShader, const string& fragShader);
		/// @brief Load and compile a shader in OpenGl.
		/// @param vertShader Vertex shader file path.
		/// @param fragShader Fragment shader file path.
		/// @return Compiled shader.
		static Shader* LoadShader(const char* vertPath, const char* fragPath);
		/// @brief Unload shader from OpenGL.
		/// @param shader Shader to unload.
		static void FreeShader(Shader& shader);
	};

	/// @brief OpenGL texture & metadata.
	struct Texture
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
		static Texture* MakeTexture(unsigned width, unsigned height, unsigned channels, const unsigned char* pixels);
		/// @brief Load a texture into OpenGL from a file.
		/// @param imagePath Texture file path.
		/// @return 
		static Texture* LoadTexture(const char* imagePath);
		/// @brief Unload a texture from OpenGL.
		/// @param tex Texture to unload.
		static void FreeTexture(Texture& tex);
	};

	/// @brief Directional light struct.
	struct DirectionalLight
	{
		/// @brief Light color.
		ColorRGB color;
		/// @brief Light direction.
		Vector3 direction;
	};

#pragma endregion
}

