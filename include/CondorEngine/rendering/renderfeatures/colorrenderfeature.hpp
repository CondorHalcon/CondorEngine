#pragma once
#include "CondorEngine/pch.h"
#include "CondorEngine/rendering/renderfeature.h"
#include "CondorEngine/rendering/renderer.h"
#include "CondorEngine/debug.hpp"
#include "CondorEngine/components/mesh.h"
#include "CondorEngine/sceneobject.h"

namespace CondorEngine
{
    namespace Rendering
    {
        class DllExport ColorRenderFeature : public RenderFeature
        {
        public:
            ColorRenderFeature() {}
            virtual void Render() override {
                for (Mesh* mesh : Renderer::meshes) {
                    if (mesh->material == nullptr) {
                        Debug::LogError("No material set; failed to render.");
                        return;
                    }
                    mesh->material->setTransform(mesh->getSceneObject()->getTransform());
                    mesh->material->Update();

                    // specify which shader to use
                    glUseProgram(mesh->material->getShader().program);
                    // specify which geometry
                    glBindVertexArray(mesh->data.vao);
                    // draw the geometry with the shader
                    glDrawElements(GL_TRIANGLES, mesh->data.size, GL_UNSIGNED_INT, nullptr);
                }
            }
        };
    }
}