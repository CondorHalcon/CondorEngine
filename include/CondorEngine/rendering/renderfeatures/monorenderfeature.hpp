#pragma once
#include "CondorEngine/pch.h"
#include "CondorEngine/rendering/renderfeature.h"
#include "CondorEngine/rendering/renderer.h"
#include "CondorEngine/components/mesh.h"
#include "CondorEngine/sceneobject.h"
#include "CondorEngine/material.h"

namespace CondorEngine
{
    namespace Rendering
    {
        /// @brief Render feature that renders the whole scene with a single material.
        class DllExport MonoRenderFeature : public RenderFeature
        {
        public:
            /// @brief Class constructor.
            /// @param mat Mono material to render the scene with.
            MonoRenderFeature(Material* mat) {
                material = mat;
            }

            /// @brief Mono material to render the scene with.
            Material* material;

            virtual void Render() override {
                if (material == nullptr) {
                    throw("CondorEngine::Rendering::MonoRenderFeature :: Failed to render: No mono material set.");
                }

                for (Mesh* mesh : Renderer::meshes) {
                    material->setTransform(mesh->getSceneObject()->getTransform());
                    material->Update();

                    // specify which shader to use
                    glUseProgram(material->getShader().program);
                    // specify which geometry
                    glBindVertexArray(mesh->data.vao);
                    // draw the geometry with the shader
                    glDrawElements(GL_TRIANGLES, mesh->data.size, GL_UNSIGNED_INT, nullptr);
                }
            }
        };
    }
}
