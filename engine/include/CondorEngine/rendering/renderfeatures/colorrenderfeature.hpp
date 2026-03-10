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
            REFLECT_CLASS(CondorEngine::Rendering::ColorRenderFeature, RenderFeature)
        public:
            /// @brief Class constructor.
            ColorRenderFeature() {}

            virtual void Render() override {
                RenderFeature::Render();

                for (Mesh* mesh : Renderer::meshes) {
                    if (mesh->meshData == nullptr) { continue; }
                    // filter to only render enabled layer
                    if (!mesh->getSceneObject()->layer.value & Camera::Main()->layerMask.value) { continue; }

                    if (mesh->material == nullptr) {
                        throw("CondorEngine::Rendering::ColorRenderFeature :: Failed to render: No material set to mesh component.");
                    }

                    // prep shader
                    mesh->material->setTransform(mesh->getSceneObject()->getTransform());
                    mesh->material->UpdateMat(Camera::Main());

                    // specify which shader to use
                    glUseProgram(mesh->material->getShader()->getData().program);
                    // specify which geometry
                    glBindVertexArray(mesh->meshData->getData().vao);
                    // draw the geometry with the shader
                    glDrawElements(GL_TRIANGLES, mesh->meshData->getData().size, GL_UNSIGNED_INT, nullptr);
                }
            }
        };
    }
}