#pragma once
#include "core.h"

// third party
#include "glew/glew.h"
#include "glm/glm.hpp"
#include <vector> // for the daring
#include <string>

using std::string;
using glm::mat4;
using glm::vec4;
using glm::vec3;
using glm::vec2;

namespace CondorEngine {

#pragma region Struct Definitions
	struct Vertex {
		/// <summary> vertex position </summary>
		vec4 pos;
		/// <summary> vertex color </summary>
		vec4 col;
		/// <summary> uv </summary>
		vec2 uv;
		/// <summary> vertex normal </summary>
		vec3 normal;
	};

	struct Shader
	{
		GLuint program;

		// load shaders
		static Shader* MakeShader(const char* vertShader, const char* fragShader);
		static Shader* MakeShader(const string& vertShader, const string& fragShader);
		static Shader* LoadShader(const char* vertPath, const char* fragPath);
		static void FreeShader(Shader& shader);
	};

	/// <summary> OpenGL texture & metadata. </summary>
	struct Texture
	{
		/// <summary> OpenGL texture name <summary>
		GLuint handle;
		unsigned width;
		unsigned height;
		unsigned channels;

		static Texture* MakeTexture(unsigned width, unsigned height, unsigned channels, const unsigned char* pixels);
		static Texture* LoadTexture(const char* imagePath);
		static void FreeTexture(Texture& tex);
	};

	struct Light
	{
		vec3 color;
		vec3 direction;
	};

#pragma endregion
}

