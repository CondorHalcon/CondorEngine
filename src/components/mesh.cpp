#include "CondorEngine/components/mesh.h"
// internal
#include "CondorEngine/debug.hpp"
#include "CondorEngine/rendering/renderer.h"
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
		Rendering::Renderer::meshes.push_back(this);
	}
}
