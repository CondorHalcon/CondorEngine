#define STB_IMAGE_IMPLEMENTATION
#include "renderer.h"
#include <vector>
#include <fstream> // for reading from files
#include <string>
#include "glm/ext.hpp"
#include "stb/stb_image.h" // for image loading

using std::fstream;

#pragma region Geometry Implementation

Geometry MakeGeometry(const Vertex* const verts, GLsizei vertCount, const GLuint* indices, GLsizei indexCount)
{
	// create GPU instance
	Geometry geo = {}; //zero-initialize
	geo.size = indexCount;

	// make buffers
	glGenVertexArrays(1, &geo.vao); // make a VAO at this geo's point in memory
	glGenBuffers(1, &geo.vbo);
	glGenBuffers(1, &geo.ibo);

	// bind the buffers for the task which we want them to do, like and angry spirit
	glBindVertexArray(geo.vao);
	glBindBuffer(GL_ARRAY_BUFFER, geo.vbo);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, geo.ibo);

	// use vertex data if using vectors.. the GPU manufaturer determins how to draw it
	glBufferData(GL_ARRAY_BUFFER, vertCount * sizeof(Vertex), verts, GL_STATIC_DRAW);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, indexCount * sizeof(GLuint), indices, GL_STATIC_DRAW);

#pragma region Enable Vertex Attributes
	// describe the buffer
	glEnableVertexAttribArray(0); // attribute index for enabling positions
	glVertexAttribPointer(
		0, // attribute index
		4, // no. of componenrts
		GL_FLOAT, // type of componenetd
		GL_FALSE, // should be normalized?
		sizeof(Vertex), // size/stride in bites of each vertex position
		(void*)0);
	// vertex color blending
	glEnableVertexAttribArray(1); // attribute index for enabling positions
	glVertexAttribPointer(
		1, // attribute index
		4, // no. of componenrts
		GL_FLOAT, // type of componenetd
		GL_FALSE, // should be normalized?
		sizeof(Vertex), // size/stride in bites of each vertex position
		(void*)offsetof(Vertex, col));

	// UV
	glEnableVertexAttribArray(2); // attribute index for enabling positions
	glVertexAttribPointer(
		2, // attribute index
		2, // no. of componenrts
		GL_FLOAT, // type of componenetd
		GL_FALSE, // should be normalized?
		sizeof(Vertex), // size/stride in bites of each vertex position
		(void*)offsetof(Vertex, uv));
	// normals
	glEnableVertexAttribArray(3); // attribute index for enabling positions
	glVertexAttribPointer(
		3, // attribute index
		3, // no. of componenrts
		GL_FLOAT, // type of componenetd
		GL_FALSE, // should be normalized?
		sizeof(Vertex), // size/stride in bites of each vertex position
		(void*)offsetof(Vertex, normal));
#pragma endregion

	// unbind the angry spirit and bind it to nothing
	glBindVertexArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

	return geo;
}

Geometry MakeGeometry(const std::vector<Vertex> verts, const std::vector<GLuint> indices)
{
	return MakeGeometry(verts.data(), verts.size(), indices.data(), indices.size());
}

void FreeGeometry(Geometry& geo)
{
	// reverse the order so we don't ose acces to ibo and vbo
	glDeleteBuffers(1, &geo.ibo);
	glDeleteBuffers(1, &geo.vbo);
	glDeleteVertexArrays(1, &geo.vao);
	// zero out the geo so its gone from gpu memory
	geo = {};
}

void DrawGeometry(const Shader& shader, const Geometry& geo)
{
	// specify which shader to use
	glUseProgram(shader.program);
	// specify which geometry
	glBindVertexArray(geo.vao);
	// draw the geometry with the shader
	glDrawElements(GL_TRIANGLES, geo.size, GL_UNSIGNED_INT, nullptr);
}

#pragma endregion

#pragma region Shader Impementations

void ReportCompileStatus(GLuint& shaderToReport) {
	GLint compileStatus = 0;
	glGetShaderiv(shaderToReport, GL_COMPILE_STATUS, &compileStatus);
	if (compileStatus != GL_TRUE) {
		//TODO: get the error report and print it out
	}
}

Shader MakeShader(const char* vertShader, const char* fragShader)
{
	//TODO: add error handling/checking logic to shader process

	// make an instance of the shader
	Shader shader = {};
	shader.program = glCreateProgram();

	GLuint vertexPortion = glCreateShader(GL_VERTEX_SHADER);
	GLuint fragPortion = glCreateShader(GL_FRAGMENT_SHADER);

	// load the shader source code
	glShaderSource(vertexPortion, 1, &vertShader, 0);
	glShaderSource(fragPortion, 1, &fragShader, 0);

	// compile shaders
	//NOTE: this is where you would detect if something is wrong
	glCompileShader(vertexPortion);
	glCompileShader(fragPortion);

	// assemble the final shader from the two shaders
	glAttachShader(shader.program, vertexPortion);
	glAttachShader(shader.program, fragPortion);

	//link the shaders together
	glLinkProgram(shader.program);
	//TODO: error check the link

	glDeleteShader(vertexPortion);
	glDeleteShader(fragPortion);

	return shader;
}

Shader MakeShader(const string& vertShader, const string& fragShader)
{
	return MakeShader(vertShader.c_str(), fragShader.c_str());
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

Shader LoadShader(const char* vertPath, const char* fragPath)
{
	std::string vertSource = ReadFile(vertPath);
	std::string fragSource = ReadFile(fragPath);

	return MakeShader(vertSource, fragSource);
}

void FreeShader(Shader& shader)
{
	glDeleteProgram(shader.program);
	// zero it out
	shader = {};
}

#pragma endregion

#pragma region Uniform Sends

void SetUniform(const Shader& shader, GLuint location, const mat4& value)
{
	glProgramUniformMatrix4fv(shader.program, location, 1, GL_FALSE, glm::value_ptr(value));
}

void SetUniform(const Shader& shader, GLuint location, const Texture& value, int textureSlot)
{
	glActiveTexture(GL_TEXTURE0 + textureSlot);
	glBindTexture(GL_TEXTURE_2D, value.handle);
	glProgramUniform1i(shader.program, location, textureSlot);
}

void SetUniform(const Shader& shader, GLuint location, const vec4& value)
{
	glProgramUniform4fv(shader.program, location, 1, glm::value_ptr(value));
}

void SetUniform(const Shader& shader, GLuint location, const vec3& value)
{
	glProgramUniform3fv(shader.program, location, 1, glm::value_ptr(value));
}

#pragma endregion

#pragma region Texture Implementation

Texture MakeTexture(unsigned width, unsigned height, unsigned channels, const unsigned char* pixels)
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
	Texture texObject = { 0, width, height, channels };
	// generate the texture on the GPU with the struct we made.
	glGenTextures(1, &texObject.handle);
	// bind and buffer texture
	glBindTexture(GL_TEXTURE_2D, texObject.handle);
	glTexImage2D(GL_TEXTURE_2D, 0, oglFormat, width, height, 0, oglFormat, GL_UNSIGNED_BYTE, pixels);
	// configure texture settings
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	// unbind and return the object
	glBindTexture(GL_TEXTURE_2D, 0);
	return texObject;
}

Texture LoadTexture(const char* imagePath)
{
	// setup variables to store texture data
	int imageWidth = -1;
	int imageHeight = -1;
	int imageFormat = -1;
	unsigned char* imagePixels = nullptr;

	Texture newTex = {};
	// load the data!
	stbi_set_flip_vertically_on_load(true); // load using OpenGL conventions
	imagePixels = stbi_load(
		imagePath,
		&imageWidth,
		&imageHeight,
		&imageFormat,
		STBI_default ); // detect channels
	// NOTE: stbi_load() will return a nullptr if it failed to load

	// pass the data to OpenGL
	newTex = MakeTexture(imageWidth, imageHeight, imageFormat, imagePixels);
	// free the RAM
	stbi_image_free(imagePixels);
	imagePixels = nullptr;

	// return the texture
	return newTex;
}

void FreeTexture(Texture& tex)
{
	glDeleteTextures(1, &tex.handle);
	tex = { };
}

#pragma endregion
