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

#pragma region Struct Definitions
namespace CondorEngine {
	class Mesh : public Component {
	public:
		Mesh(SceneObject* owner);
		Mesh(SceneObject* owner, const Vertex* const verts, GLsizei vertCount, const GLuint* indices, GLsizei indexCount);
		Mesh(SceneObject* owner, const std::vector<Vertex> verts, const std::vector<GLuint> indices);
		static Mesh LoadMeshFromFile(SceneObject* owner, const char* filename);
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
		Shader shader;
	public:
		/// <summary> PreDraw calls. Best used for setting shader uniforms. </summary>
		virtual void PreDraw();
		void Draw();
		void Update() override;
		Shader* getShader();
		void setShader(Shader shader);
	};
}
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

struct Geometry {
	/// <summary> vertex array object </summary>
	GLuint vao;
	/// <summary> vertex buffer object </summary>
	GLuint vbo;
	/// <summary> index buffer object </summary>
	GLuint ibo;
	/// <summary> index count </summary>
	GLuint size;
};

struct Shader
{
	GLuint program;
};

/// <summary> OpenGL texture & metadata. </summary>
struct Texture
{
	/// <summary> OpenGL texture name <summary>
	GLuint handle;
	unsigned width;
	unsigned height;
	unsigned channels;
};

struct Light
{
	vec3 color;
	vec3 direction;
};

#pragma endregion

#pragma region Geometry Functions

Geometry MakeGeometry(const Vertex* const verts, GLsizei vertCount, const GLuint* indices, GLsizei indexCount);
// optional, not required
Geometry MakeGeometry(const std::vector<Vertex> verts, const std::vector<GLuint> indices);
void FreeGeometry(Geometry& geo);
void DrawGeometry(const Shader& shader, const Geometry& geo);

#pragma endregion

#pragma region Shader Functions

Shader MakeShader(const char* vertShader, const char* fragShader);
Shader MakeShader(const string& vertShader, const string& fragShader);
Shader LoadShader(const char* vertPath, const char* fragPath);
void FreeShader(Shader& shader);

#pragma endregion


#pragma region Uniform Functions

void SetUniform(const Shader& shader, GLuint location, const mat4& value); // for transforms
void SetUniform(const Shader& shader, GLuint location, const Texture& value, int textureSlot); // for textures
void SetUniform(const Shader& shader, GLuint location, const vec4& value); // for color and quaternions
void SetUniform(const Shader& shader, GLuint location, const vec3& value); // for rgb color & positions

#pragma endregion

#pragma region Texture Functions

Texture MakeTexture(unsigned width, unsigned height, unsigned channels, const unsigned char* pixels);
Texture LoadTexture(const char* imagePath);
void FreeTexture(Texture& tex);

#pragma endregion
