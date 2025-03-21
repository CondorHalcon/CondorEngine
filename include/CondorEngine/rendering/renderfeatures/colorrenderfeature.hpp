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
        /// @brief Render feature that renders the scene with mesh assigned materials.
        class DllExport ColorRenderFeature : public RenderFeature
        {
        public:
            /// @brief Class constructor.
            ColorRenderFeature() {}

            /// @brief Render filter's layer mask.
            unsigned int renderLayer{ 0x1 };

            virtual void Render() override {
                for (Mesh* mesh : Renderer::meshes) {
                    // filter to only render enabled layer
                    if (!mesh->getSceneObject()->layer & renderLayer) { continue; }

                    if (mesh->material == nullptr) {
                        throw("CondorEngine::Rendering::ColorRenderFeature :: Failed to render: No material set to mesh component.");
                    }

                    // prep shader
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