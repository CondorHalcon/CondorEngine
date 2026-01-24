#define STB_IMAGE_IMPLEMENTATION
#include "CondorEngine/rendering/renderer.h"
#include "CondorEngine/rendering/renderfeature.h"
// third party
#include <glew.h>
#include <glm/glm.hpp>
#include <glm/ext.hpp>
#include <stb_image.h> // for image loading
#include <assimp/scene.h>
#include <assimp/cimport.h>
// std
#include <fstream> // for reading from files
// internal
#include "CondorEngine/application.h"
#include "CondorEngine/debug.hpp"
#include "CondorEngine/material.h"
#include "CondorEngine/components/camera.h"
#include "CondorEngine/components/mesh.h"
#include "CondorEngine/components/light.h"
#include "CondorEngine/sceneobject.h"

using std::fstream;

#pragma region MeshData

CondorEngine::MeshData CondorEngine::MeshData::MakeMesh(const Vertex* const verts, GLsizei vertCount, const GLuint* indices, GLsizei indexCount) {
	MeshData mesh{};

	// create GPU instance
	mesh.size = indexCount;

	// make buffers
	glGenVertexArrays(1, &mesh.vao); // make a VAO at this geo's point in memory
	glGenBuffers(1, &mesh.vbo);
	glGenBuffers(1, &mesh.ibo);

	// bind the buffers for the task which we want them to do, like and angry spirit
	glBindVertexArray(mesh.vao);
	glBindBuffer(GL_ARRAY_BUFFER, mesh.vbo);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mesh.ibo);

	// use vertex data if using vectors.. the GPU manufacturer determins how to draw it
	glBufferData(GL_ARRAY_BUFFER, vertCount * sizeof(Vertex), verts, GL_STATIC_DRAW);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, indexCount * sizeof(GLuint), indices, GL_STATIC_DRAW);

	// describe the buffer
	glEnableVertexAttribArray(0); // attribute index for enabling positions
	glVertexAttribPointer(
		0,				// attribute index
		4,				// no. of components
		GL_FLOAT,		// type of component
		GL_FALSE,		// should be normalized?
		sizeof(Vertex), // size/stride in bites of each vertex position
		(void*)0);
	// vertex color blending
	glEnableVertexAttribArray(1); // attribute index for enabling positions
	glVertexAttribPointer(
		1,				// attribute index
		4,				// no. of components
		GL_FLOAT,		// type of component
		GL_FALSE,		// should be normalized?
		sizeof(Vertex), // size/stride in bites of each vertex position
		(void*)offsetof(Vertex, col));

	// UV
	glEnableVertexAttribArray(2); // attribute index for enabling positions
	glVertexAttribPointer(
		2,				// attribute index
		2,				// no. of components
		GL_FLOAT,		// type of component
		GL_FALSE,		// should be normalized?
		sizeof(Vertex), // size/stride in bites of each vertex position
		(void*)offsetof(Vertex, uv));
	// normals
	glEnableVertexAttribArray(3); // attribute index for enabling positions
	glVertexAttribPointer(
		3,				// attribute index
		3,				// no. of components
		GL_FLOAT,		// type of component
		GL_FALSE,		// should be normalized?
		sizeof(Vertex), // size/stride in bites of each vertex position
		(void*)offsetof(Vertex, normal));

	// unbind the angry spirit and bind it to nothing
	glBindVertexArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

	return mesh;
}

CondorEngine::MeshData CondorEngine::MeshData::MakeMesh(const std::vector<Vertex> verts, const std::vector<GLuint> indices) {
	return MakeMesh(verts.data(), verts.size(), indices.data(), indices.size());
}

CondorEngine::MeshData CondorEngine::MeshData::LoadMesh(const char* filepath) {
	// read vertices from the model
	const aiScene* scene = aiImportFile(filepath, 0);

	// just use the first mesh we find for now
	// TODO support multiple meshes in a single file
	aiMesh* mesh = scene->mMeshes[0];

	// extract indicies from the first mesh
	int numFaces = mesh->mNumFaces;
	std::vector<unsigned int> indices;

	for (int i = 0; i < numFaces; i++) {
		indices.push_back(mesh->mFaces[i].mIndices[0]);
		indices.push_back(mesh->mFaces[i].mIndices[1]);
		indices.push_back(mesh->mFaces[i].mIndices[2]);

		// generate second triangle for quads
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
		vertex.pos = Vector4{ mesh->mVertices[i].x, mesh->mVertices[i].y, mesh->mVertices[i].z, 1 };
		if (mesh->HasVertexColors(i)) {
			aiColor4D* vertColor = mesh->mColors[i];
			vertex.col = Color{ vertColor->r, vertColor->g, vertColor->b, vertColor->a };
		}
		else {
			vertex.col = Color{ 1, 1, 1, 1 };
		}
		if (mesh->HasTextureCoords(0)) {
			vertex.uv = Vector2{ mesh->mTextureCoords[0][i].x, mesh->mTextureCoords[0][i].y };
		}
		else {
			vertex.uv = Vector2{ 0, 0 };
		}
		if (mesh->HasNormals()) {
			vertex.normal = Vector3{ mesh->mNormals[i].x, mesh->mNormals[i].y, mesh->mNormals[i].z };
		}
		else {
			vertex.normal = Vector3{ 0, 0, 1 };
		}
		vertices.push_back(vertex);
	}

	// return final
	return MakeMesh(vertices.data(), numV, indices.data(), indices.size());
}
void CondorEngine::MeshData::FreeMesh(MeshData& mesh) {
	// reverse the order so we don't ose access to ibo and vbo
	glDeleteBuffers(1, &mesh.ibo);
	glDeleteBuffers(1, &mesh.vbo);
	glDeleteVertexArrays(1, &mesh.vao);
}
#pragma endregion

#pragma region Shader Implementations

void ReportCompileStatus(GLuint& shaderToReport) {
	GLint compileStatus = 0;
	glGetShaderiv(shaderToReport, GL_COMPILE_STATUS, &compileStatus);
	if (compileStatus != GL_TRUE) {
		// TODO: get the error report and print it out
	}
}

std::string ReadFile(const char* path) {
	fstream stream(path, std::ios_base::in);
	std::string source;

	// TODO: add error checking and validation if you are reading from a text file.

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

CondorEngine::Shader CondorEngine::Shader::MakeShader(const char* vertShader, const char* fragShader) {
	// TODO: add error handling/checking logic to shader process

	// make an instance of the shader
	Shader shader{};
	shader.program = glCreateProgram();

	GLuint vertexPortion = glCreateShader(GL_VERTEX_SHADER);
	GLuint fragPortion = glCreateShader(GL_FRAGMENT_SHADER);

	// load the shader source code
	glShaderSource(vertexPortion, 1, &vertShader, 0);
	glShaderSource(fragPortion, 1, &fragShader, 0);

	// compile shaders
	// NOTE: this is where you would detect if something is wrong
	glCompileShader(vertexPortion);
	glCompileShader(fragPortion);

	// check compile status
	GLint vertParam;
	GLint fragParam;
	glGetShaderiv(vertexPortion, GL_COMPILE_STATUS, &vertParam);
	glGetShaderiv(vertexPortion, GL_COMPILE_STATUS, &fragParam);
	Debug::Log("CondorEngine::Shader :: Shader Compile Status: Vertex[" + std::to_string(vertParam) + "]; Fragment[" + std::to_string(fragParam) + "]");

	// assemble the final shader from the two shaders
	glAttachShader(shader.program, vertexPortion);
	glAttachShader(shader.program, fragPortion);

	// link the shaders together
	glLinkProgram(shader.program);
	// TODO: error check the link

	glDeleteShader(vertexPortion);
	glDeleteShader(fragPortion);

	return shader;
}

CondorEngine::Shader CondorEngine::Shader::MakeShader(const std::string& vertShader, const std::string& fragShader) {
	return CondorEngine::Shader::MakeShader(vertShader.c_str(), fragShader.c_str());
}

CondorEngine::Shader CondorEngine::Shader::LoadShader(const char* vertPath, const char* fragPath) {
	std::string vertSource = ReadFile(vertPath);
	std::string fragSource = ReadFile(fragPath);

	return CondorEngine::Shader::MakeShader(vertSource, fragSource);
}

void CondorEngine::Shader::FreeShader(Shader& shader) {
	glDeleteProgram(shader.program);
	// zero it out
	shader = {};
}

#pragma endregion

#pragma region Texture

CondorEngine::Texture CondorEngine::Texture::MakeTexture(unsigned width, unsigned height, unsigned channels, const unsigned char* pixels) {
	GLenum oglFormat = GL_RGBA;
	switch (channels) {
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
	Texture texObject{ 0, width, height, channels };
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

CondorEngine::Texture CondorEngine::Texture::LoadTexture(const char* imagePath) {
	// setup variables to store texture data
	int imageWidth = -1;
	int imageHeight = -1;
	int imageFormat = -1;
	unsigned char* imagePixels = nullptr;

	Texture newTex{};
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

void CondorEngine::Texture::FreeTexture(Texture& tex) {
	glDeleteTextures(1, &tex.handle);
	tex = {};
}

#pragma endregion

#pragma region Directional Light

CondorEngine::DirectionalLight::DirectionalLight(ColorRGB col, Vector3 dir) {
	color = col;
	direction = dir;
}

CondorEngine::DirectionalLight::DirectionalLight() : DirectionalLight(ColorRGB{ .7f, .7f, .7f }, Vector3{ 0, 0, -1 }) {}

#pragma endregion

#pragma region Renderer

CondorEngine::Rendering::Renderer* CondorEngine::Rendering::Renderer::instance = nullptr;
std::vector<CondorEngine::Mesh*> CondorEngine::Rendering::Renderer::meshes = std::vector<CondorEngine::Mesh*>();
std::vector<CondorEngine::Light*> CondorEngine::Rendering::Renderer::lights = std::vector<CondorEngine::Light*>();

CondorEngine::Rendering::Renderer::Renderer() {
	features = std::vector<RenderFeature*>();
	clearColor = ColorRGB{ .4, .4, .4 };
}

CondorEngine::Rendering::Renderer::~Renderer() {
	if (instance == this) {
		instance = nullptr;
	}

	for (auto feature : features) {
		delete feature;
	}
}

CondorEngine::Rendering::Renderer* CondorEngine::Rendering::Renderer::Instance() {
	if (instance == nullptr) {
		instance = new Renderer();
	}
	return instance;
}

void CondorEngine::Rendering::Renderer::init() {
	// start setting up graphics pipeline
	glewInit();
	// set flags for openGL features
	glEnable(GL_BLEND);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_STENCIL_TEST);
	glEnable(GL_CULL_FACE); // optimization features

	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glDepthFunc(GL_LEQUAL); // depth testing for deciding which objects are in front of one another
	glFrontFace(GL_CCW);	// winding order for determining which direction the normal is on a triangle
	glCullFace(GL_BACK);

	// enable OpenGL debug output
	glEnable(GL_DEBUG_OUTPUT);
	glDebugMessageCallback(Debug::GLMessageCallback, 0);

	glClearColor(clearColor.r, clearColor.g, clearColor.b, 1);

	std::string message = "CondorEngine::Application :: [OpenGL Environment]\n";
	message.append("\t- OpenGL version: " + std::string((const char*)glGetString(GL_VERSION)) + "\n");
	message.append("\t- GLEW version: " + std::string((const char*)glewGetString(GLEW_VERSION)) + "\n");
	message.append("\t- Renderer: " + std::string((const char*)glGetString(GL_RENDERER)) + "\n");
	message.append("\t- GLSL: " + std::string((const char*)glGetString(GL_SHADING_LANGUAGE_VERSION)));
	Debug::Log(message);
}

void CondorEngine::Rendering::Renderer::Render() {
	if (Camera::Main() == nullptr) { // no camera to render with
		ResetScreen();
		return;
	}

	// pre processing
	for (RenderFeature* feature : features) {
		feature->PreProccess();
	}

	ResetScreen();

	// main render
	for (RenderFeature* feature : features) {
		feature->Render();
	}

	// post processing
	for (RenderFeature* feature : features) {
		feature->PostProcess();
	}

	meshes.clear();
	lights.clear();
}

void CondorEngine::Rendering::Renderer::ResetScreen() {
	Vector2Int window = Application::Instance()->getWindowDimensions();
	glViewport(0, 0, window.x, window.y);
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
	// clear the screen, depth, and stencil buffers each frame
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
}
#pragma endregion

