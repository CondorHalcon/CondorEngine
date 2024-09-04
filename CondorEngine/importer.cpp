#include "importer.h"

#include <assimp/scene.h>
#include <assimp/cimport.h>
#include <vector>

Geometry MakeGeometryFromFile(const char* filename)
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
            vertex.col = vec4{1,1,1,1};
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

    Geometry geo = MakeGeometry(vertices.data(), numV, indices.data(), indices.size());

    return geo;
}
