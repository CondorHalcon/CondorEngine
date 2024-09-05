#define STB_IMAGE_IMPLEMENTATION
#include "renderer.h"
#include "camera.h"
// std
#include <vector>
#include <fstream> // for reading from files
#include <string>
// third party
#include "glm/ext.hpp"
#include "stb/stb_image.h" // for image loading
#include <assimp/scene.h>
#include <assimp/cimport.h>

using std::fstream;

#pragma region Shader Impementations

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

CondorEngine::Shader CondorEngine::Shader::MakeShader(const char* vertShader, const char* fragShader)
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

CondorEngine::Shader CondorEngine::Shader::MakeShader(const string& vertShader, const string& fragShader)
{
	return CondorEngine::Shader::MakeShader(vertShader.c_str(), fragShader.c_str());
}

CondorEngine::Shader CondorEngine::Shader::LoadShader(const char* vertPath, const char* fragPath)
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

CondorEngine::Shader CondorEngine::Shader::LoadBasicShader()
{
	return LoadShader("shaders/basic.vert", "shaders/basic.frag");
}

CondorEngine::Shader CondorEngine::Shader::LoadDiffuseShader()
{
	return LoadShader("shaders/directional.vert", "shaders/phong.frag");
}

CondorEngine::Shader CondorEngine::Shader::LoadUVShader()
{
	return LoadShader("shaders/basic.vert", "shaders/uv.frag");
}

CondorEngine::Shader CondorEngine::Shader::LoadNormalShader(bool isObjectSpace)
{
	if (isObjectSpace) {
		return LoadShader("shaders/basic.vert", "shaders/normal.frag");
	}
	else {
		return LoadShader("shaders/directional.vert", "shaders/normal.frag");
	}
}

#pragma endregion

#pragma region Texture

CondorEngine::Texture CondorEngine::Texture::MakeTexture(unsigned width, unsigned height, unsigned channels, const unsigned char* pixels)
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

CondorEngine::Texture CondorEngine::Texture::LoadTexture(const char* imagePath)
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

#pragma region Mesh

CondorEngine::Mesh::Mesh() : CondorEngine::Component()
{
	this->material = nullptr;
}

CondorEngine::Mesh::Mesh(const Vertex* const verts, GLsizei vertCount, const GLuint* indices, GLsizei indexCount)
{
	// create GPU instance
	this->size = indexCount;

	// make buffers
	glGenVertexArrays(1, &this->vao); // make a VAO at this geo's point in memory
	glGenBuffers(1, &this->vbo);
	glGenBuffers(1, &this->ibo);

	// bind the buffers for the task which we want them to do, like and angry spirit
	glBindVertexArray(vao);
	glBindBuffer(GL_ARRAY_BUFFER, this->vbo);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->ibo);

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
}

CondorEngine::Mesh::Mesh(const std::vector<Vertex> verts, const std::vector<GLuint> indices) : CondorEngine::Mesh::Mesh(verts.data(), verts.size(), indices.data(), indices.size())
{
}

CondorEngine::Mesh CondorEngine::Mesh::LoadMeshFromFile(const char* filename)
{
	// read verticies from the model
	const aiScene* scene = aiImportFile(filename, 0);

	// just use the first mesh we find for now
	aiMesh* mesh = scene->mMeshes[0];

	// extract indicies from the first mesh
	int numFaces = mesh->mNumFaces;
	std::vector<unsigned int> indices;

	for (int i = 0; i < numFaces; i++) {
		indices.push_back(mesh->mFaces[i].mIndices[0]);
		indices.push_back(mesh->mFaces[i].mIndices[1]);
		indices.push_back(mesh->mFaces[i].mIndices[2]);

		// generate second trianle for quads
		if (mesh->mFaces[i].mNumIndices == 4) {
			indices.push_back(mesh->mFaces[i].mIndices[0]);
			indices.push_back(mesh->mFaces[i].mIndices[2]);
			indices.push_back(mesh->mFaces[i].mIndices[3]);
		}
	}

	// extract vertex data
	int numV = mesh->mNumVertices;
	std::vector<Vertex> vertices = std::vector<Vertex>();
	for (int i = 0; i < numV; i++) {
		Vertex vertex;
		vertex.pos = glm::vec4{ mesh->mVertices[i].x, mesh->mVertices[i].y, mesh->mVertices[i].z, 1 };
		if (mesh->HasVertexColors(i)) {
			aiColor4D* vertColor = mesh->mColors[i];
			vertex.col = glm::vec4{ vertColor->r, vertColor->g, vertColor->b, vertColor->a };
		}
		else {
			vertex.col = vec4{ 1,1,1,1 };
		}
		if (mesh->HasTextureCoords(i)) {
			vertex.uv = glm::vec2{ mesh->mTextureCoords[i]->x, mesh->mTextureCoords[i]->y };
		}
		else {
			vertex.uv = glm::vec2{ 0,0 };
		}
		if (mesh->HasNormals()) {
			vertex.normal = glm::vec3{ mesh->mNormals[i].x, mesh->mNormals[i].y, mesh->mNormals[i].z };
		}
		else {
			vertex.normal = glm::vec3{ 0,0,1 };
		}
		vertices.push_back(vertex);
	}

	return Mesh(vertices.data(), numV, indices.data(), indices.size());
}

CondorEngine::Mesh::~Mesh()
{
	// reverse the order so we don't ose acces to ibo and vbo
	glDeleteBuffers(1, &ibo);
	glDeleteBuffers(1, &vbo);
	glDeleteVertexArrays(1, &vao);
}

void CondorEngine::Mesh::Update()
{
	material->setTransform(getSceneObject()->transform);
	material->Update();

	// specify which shader to use
	glUseProgram(material->getShader()->program);
	// specify which geometry
	glBindVertexArray(vao);
	// draw the geometry with the shader
	glDrawElements(GL_TRIANGLES, size, GL_UNSIGNED_INT, nullptr);
}

#pragma endregion

#pragma region Material

CondorEngine::Material::Material(Shader* shader)
{
	this->shader = shader;
	this->transform = glm::identity<mat4>();
}

void CondorEngine::Material::Update()
{
	SetUniform(0, Camera::Instance()->projectionMatrix);
	SetUniform(1, Camera::Instance()->viewMatrix);
	SetUniform(2, transform);
}

void CondorEngine::Material::setShader(Shader* shader)
{
	this->shader = shader;
}

CondorEngine::Shader* CondorEngine::Material::getShader()
{
	return this->shader;
}

void CondorEngine::Material::setTransform(glm::mat4 transform)
{
}

void CondorEngine::Material::SetUniform(GLuint location, const mat4& value)
{
	glProgramUniformMatrix4fv(shader->program, location, 1, GL_FALSE, glm::value_ptr(value));
}

void CondorEngine::Material::SetUniform(GLuint location, const Texture& value, int textureSlot)
{
	glActiveTexture(GL_TEXTURE0 + textureSlot);
	glBindTexture(GL_TEXTURE_2D, value.handle);
	glProgramUniform1i(shader->program, location, textureSlot);
}

void CondorEngine::Material::SetUniform(GLuint location, const vec4& value)
{
	glProgramUniform4fv(shader->program, location, 1, glm::value_ptr(value));
}

void CondorEngine::Material::SetUniform(GLuint location, const vec3& value)
{
	glProgramUniform3fv(shader->program, location, 1, glm::value_ptr(value));
}

#pragma endregion


