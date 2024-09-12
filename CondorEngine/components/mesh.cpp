#include "mesh.h"
#include "../renderer.h"
#include "../camera.h"
#include "../debug.h"
// third party
#include <assimp/scene.h>
#include <assimp/cimport.h>
#include "glm/ext.hpp"

#pragma region Mesh

CondorEngine::Mesh::Mesh(const Vertex* const verts, GLsizei vertCount, const GLuint* indices, GLsizei indexCount)
{
	this->name = "CondorEngine::Mesh";
	this->material = nullptr;

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

	// use vertex data if using vectors.. the GPU manufacturer determins how to draw it
	glBufferData(GL_ARRAY_BUFFER, vertCount * sizeof(Vertex), verts, GL_STATIC_DRAW);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, indexCount * sizeof(GLuint), indices, GL_STATIC_DRAW);

#pragma region Enable Vertex Attributes
	// describe the buffer
	glEnableVertexAttribArray(0); // attribute index for enabling positions
	glVertexAttribPointer(
		0, // attribute index
		4, // no. of components
		GL_FLOAT, // type of component
		GL_FALSE, // should be normalized?
		sizeof(Vertex), // size/stride in bites of each vertex position
		(void*)0);
	// vertex color blending
	glEnableVertexAttribArray(1); // attribute index for enabling positions
	glVertexAttribPointer(
		1, // attribute index
		4, // no. of components
		GL_FLOAT, // type of component
		GL_FALSE, // should be normalized?
		sizeof(Vertex), // size/stride in bites of each vertex position
		(void*)offsetof(Vertex, col));

	// UV
	glEnableVertexAttribArray(2); // attribute index for enabling positions
	glVertexAttribPointer(
		2, // attribute index
		2, // no. of components
		GL_FLOAT, // type of component
		GL_FALSE, // should be normalized?
		sizeof(Vertex), // size/stride in bites of each vertex position
		(void*)offsetof(Vertex, uv));
	// normals
	glEnableVertexAttribArray(3); // attribute index for enabling positions
	glVertexAttribPointer(
		3, // attribute index
		3, // no. of components
		GL_FLOAT, // type of component
		GL_FALSE, // should be normalized?
		sizeof(Vertex), // size/stride in bites of each vertex position
		(void*)offsetof(Vertex, normal));
#pragma endregion

	// unbind the angry spirit and bind it to nothing
	glBindVertexArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

CondorEngine::Mesh::Mesh(const std::vector<Vertex> verts, const std::vector<GLuint> indices) :
	CondorEngine::Mesh::Mesh(verts.data(), verts.size(), indices.data(), indices.size()) { }

CondorEngine::Mesh* CondorEngine::Mesh::LoadMeshFromFile(const char* filename)
{
	// read vertices from the model
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
			vertex.col = Color{ 1,1,1,1 };
		}
		if (mesh->HasTextureCoords(i)) {
			vertex.uv = Vector2{ mesh->mTextureCoords[i]->x, mesh->mTextureCoords[i]->y };
		}
		else {
			vertex.uv = Vector2{ 0,0 };
		}
		if (mesh->HasNormals()) {
			vertex.normal = Vector3{ mesh->mNormals[i].x, mesh->mNormals[i].y, mesh->mNormals[i].z };
		}
		else {
			vertex.normal = Vector3{ 0,0,1 };
		}
		vertices.push_back(vertex);
	}

	return new Mesh(vertices.data(), numV, indices.data(), indices.size());
}

CondorEngine::Mesh::~Mesh()
{
	// reverse the order so we don't ose access to ibo and vbo
	glDeleteBuffers(1, &ibo);
	glDeleteBuffers(1, &vbo);
	glDeleteVertexArrays(1, &vao);
}

void CondorEngine::Mesh::Update()
{
	if (material == nullptr) { 
		Debug::LogError("No material set; failed to render.");
		return; 
	}
	material->setTransform(getSceneObject()->getTransform());
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
	this->name = "CondorEngine::Material";
	this->shader = shader;
	this->transform = glm::identity<Transform>();
}

void CondorEngine::Material::Update()
{
	if (Camera::Main() != nullptr) {
		SetUniform(0, CondorEngine::Camera::Main()->getProjectionMatrix());
		SetUniform(1, CondorEngine::Camera::Main()->getViewMatrix());
	} else {
		SetUniform(0, glm::perspective(glm::radians(60.0f), 640 / (float)480, .01f, 10.0f));
		SetUniform(1, glm::lookAt(
		Vector3{ 0,0,0 }, // camera position
		Vector3{ 0,0,1 }, // look at postion
		Vector3{ 0,1,0 }) // up vector
		);
	}
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

void CondorEngine::Material::setTransform(Transform transform)
{
	this->transform = transform;
}

void CondorEngine::Material::SetUniform(GLuint location, const Transform& value)
{
	glProgramUniformMatrix4fv(shader->program, location, 1, GL_FALSE, glm::value_ptr(value));
}

void CondorEngine::Material::SetUniform(GLuint location, const Texture& value, int textureSlot)
{
	glActiveTexture(GL_TEXTURE0 + textureSlot);
	glBindTexture(GL_TEXTURE_2D, value.handle);
	glProgramUniform1i(shader->program, location, textureSlot);
}

void CondorEngine::Material::SetUniform(GLuint location, const glm::vec3& value)
{
	glProgramUniform3fv(shader->program, location, 1, glm::value_ptr(value));
}

void CondorEngine::Material::SetUniform(GLuint location, const glm::vec4& value)
{
	glProgramUniform4fv(shader->program, location, 1, glm::value_ptr(value));
}

#pragma endregion
