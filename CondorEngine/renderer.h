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
	class Material;

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
		static Shader MakeShader(const char* vertShader, const char* fragShader);
		static Shader MakeShader(const string& vertShader, const string& fragShader);
		static Shader LoadShader(const char* vertPath, const char* fragPath);
		static void FreeShader(Shader& shader);

		// inbuilt shaders
		static Shader LoadBasicShader();
		static Shader LoadDiffuseShader();
		static Shader LoadUVShader();
		static Shader LoadNormalShader(bool isObjectSpace = false);
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

	class Mesh : public Component {
	public:
		Mesh(const Vertex* const verts, GLsizei vertCount, const GLuint* indices, GLsizei indexCount);
		Mesh(const std::vector<Vertex> verts, const std::vector<GLuint> indices);
		static Mesh* LoadMeshFromFile(const char* filename);
		~Mesh();
	private:
		/// <summary> vertex array object </summary>
		GLuint vao;
		/// <summary> vertex buffer object </summary>
		GLuint vbo;
		/// <summary> index buffer object </summary>
		GLuint ibo;
		/// <summary> index count </summary>
		GLuint size;
		/// <summary> Render shader for the mesh. </summary>
		Material* material;
	public:
		void Update() override;
	};

	class Material : public Object {
	public:
		Material(Shader* shader);
		void Update() override;
	private:
		Shader* shader;
		glm::mat4 transform;
	public:
		void setShader(Shader* shader);
		Shader* getShader();
		void setTransform(glm::mat4 transform);
	protected:
		void SetUniform(GLuint location, const mat4& value); // for transforms
		void SetUniform(GLuint location, const Texture& value, int textureSlot); // for textures
		void SetUniform(GLuint location, const vec4& value); // for color and quaternions
		void SetUniform(GLuint location, const vec3& value); // for rgb color & positions
	};
}

