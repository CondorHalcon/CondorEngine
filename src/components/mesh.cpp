#include "CondorEngine/components/mesh.h"
// internal
#include "CondorEngine/debug.hpp"
#include "CondorEngine/renderer.h"
#include "CondorEngine/sceneobject.h"
#include "CondorEngine/components/camera.h"
#include "CondorEngine/materials/phong.hpp"
// third party
#include <assimp/scene.h>
#include <assimp/cimport.h>
#include <glm/ext.hpp>

CondorEngine::Mesh::Mesh(MeshData meshData, Material* material) {
	this->name = "CondorEngine::Mesh";
	this->data = meshData;
	this->material = material;
}
CondorEngine::Mesh::Mesh(MeshData meshData) : Mesh(meshData, new Phong()) {}

CondorEngine::Mesh::~Mesh()
{
	delete this->material;
}

void CondorEngine::Mesh::LateUpdate()
{
	if (enabled)
	{
		Renderer::meshes.push_back(this);
	}
}

void CondorEngine::Mesh::Render()
{
	if (material == nullptr)
	{
		Debug::LogError("No material set; failed to render.");
		return;
	}
	material->setTransform(getSceneObject()->getTransform());
	material->Update();

	// specify which shader to use
	glUseProgram(material->getShader().program);
	// specify which geometry
	glBindVertexArray(data.vao);
	// draw the geometry with the shader
	glDrawElements(GL_TRIANGLES, data.size, GL_UNSIGNED_INT, nullptr);
}