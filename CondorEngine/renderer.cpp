#define STB_IMAGE_IMPLEMENTATION
#include "renderer.h"
// third party
#include "glew/glew.h"
#include "glm/glm.hpp"
#include "glm/ext.hpp"
#include "stb/stb_image.h" // for image loading
// std
#include <fstream> // for reading from files
// internal
#include "debug.hpp"
#include "components/camera.h"
#include "components/mesh.h"

using std::fstream;

#pragma region Shader Implementations

void ReportCompileStatus(GLuint& shaderToReport) {
	GLint compileStatus = 0;
	glGetShaderiv(shaderToReport, GL_COMPILE_STATUS, &compileStatus);
	if (compileStatus != GL_TRUE) {
		//TODO: get the error report and print it out
	}
}

std::string ReadFile(const char* path) {
	fstream stream(path, std::ios_base::in);
	std::string source;

	//TODO: add error checking and validation if you are reading from a text file.

	while (!stream.eof()) {
		std::string thisLine;
		std::getline(stream, thisLine);
		source += thisLine + "\n";
	}

	// close the gates of hell
	stream.close();

	return source;
}

#pragma endregion

#pragma region Shader

CondorEngine::Shader* CondorEngine::Shader::MakeShader(const char* vertShader, const char* fragShader)
{
	//TODO: add error handling/checking logic to shader process

	// make an instance of the shader
	Shader* shader = new Shader{};
	shader->program = glCreateProgram();

	GLuint vertexPortion = glCreateShader(GL_VERTEX_SHADER);
	GLuint fragPortion = glCreateShader(GL_FRAGMENT_SHADER);

	// load the shader source code
	glShaderSource(vertexPortion, 1, &vertShader, 0);
	glShaderSource(fragPortion, 1, &fragShader, 0);

	// compile shaders
	//NOTE: this is where you would detect if something is wrong
	glCompileShader(vertexPortion);
	glCompileShader(fragPortion);

	// check compile status
	GLint vertParam;
	GLint fragParam;
	glGetShaderiv(vertexPortion, GL_COMPILE_STATUS, &vertParam);
	glGetShaderiv(vertexPortion, GL_COMPILE_STATUS, &fragParam);
	Debug::Log("Shader Compile Status: Vertex[" + std::to_string(vertParam) + "]; Fragment[" + std::to_string(fragParam) + "]");

	// assemble the final shader from the two shaders
	glAttachShader(shader->program, vertexPortion);
	glAttachShader(shader->program, fragPortion);

	//link the shaders together
	glLinkProgram(shader->program);
	//TODO: error check the link

	glDeleteShader(vertexPortion);
	glDeleteShader(fragPortion);

	return shader;
}

CondorEngine::Shader* CondorEngine::Shader::MakeShader(const std::string& vertShader, const std::string& fragShader)
{
	return CondorEngine::Shader::MakeShader(vertShader.c_str(), fragShader.c_str());
}

CondorEngine::Shader* CondorEngine::Shader::LoadShader(const char* vertPath, const char* fragPath)
{
	std::string vertSource = ReadFile(vertPath);
	std::string fragSource = ReadFile(fragPath);

	return CondorEngine::Shader::MakeShader(vertSource, fragSource);
}

void CondorEngine::Shader::FreeShader(Shader& shader)
{
	glDeleteProgram(shader.program);
	// zero it out
	shader = {};
}

#pragma endregion

#pragma region Texture

CondorEngine::Texture* CondorEngine::Texture::MakeTexture(unsigned width, unsigned height, unsigned channels, const unsigned char* pixels)
{
	GLenum oglFormat = GL_RGBA;
	switch (channels)
	{
	case 1:
		oglFormat = GL_RED;
		break;
	case 2:
		oglFormat = GL_RG;
		break;
	case 3:
		oglFormat = GL_RGB;
		break;
	default:
		oglFormat = GL_RGBA;
		break;
	}
	// 0 for handle, may change if you want more than one texture per mesh
	Texture* texObject = new Texture{ 0, width, height, channels };
	// generate the texture on the GPU with the struct we made.
	glGenTextures(1, &texObject->handle);
	// bind and buffer texture
	glBindTexture(GL_TEXTURE_2D, texObject->handle);
	glTexImage2D(GL_TEXTURE_2D, 0, oglFormat, width, height, 0, oglFormat, GL_UNSIGNED_BYTE, pixels);
	// configure texture settings
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	// unbind and return the object
	glBindTexture(GL_TEXTURE_2D, 0);
	return texObject;
}

CondorEngine::Texture* CondorEngine::Texture::LoadTexture(const char* imagePath)
{
	// setup variables to store texture data
	int imageWidth = -1;
	int imageHeight = -1;
	int imageFormat = -1;
	unsigned char* imagePixels = nullptr;

	Texture* newTex = {};
	// load the data!
	stbi_set_flip_vertically_on_load(true); // load using OpenGL conventions
	imagePixels = stbi_load(
		imagePath,
		&imageWidth,
		&imageHeight,
		&imageFormat,
		STBI_default); // detect channels
	// NOTE: stbi_load() will return a nullptr if it failed to load

	// pass the data to OpenGL
	newTex = MakeTexture(imageWidth, imageHeight, imageFormat, imagePixels);
	// free the RAM
	stbi_image_free(imagePixels);
	imagePixels = nullptr;

	// return the texture
	return newTex;
}

void CondorEngine::Texture::FreeTexture(Texture& tex)
{
	glDeleteTextures(1, &tex.handle);
	tex = { };
}

#pragma endregion

#pragma region Renderer

std::vector<CondorEngine::Mesh *> CondorEngine::Renderer::meshes = std::vector<CondorEngine::Mesh *>();

void CondorEngine::Renderer::Render()
{
	for (Mesh *mesh : meshes)
	{
		mesh->Render();
	}
	meshes.clear();
}

#pragma endregion
