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
            REFLECT_CLASS(CondorEngine::Rendering::MonoRenderFeature, RenderFeature)
        public:
            /// @brief Class constructor.
            /// @param mat Mono material to render the scene with.
            MonoRenderFeature(Material* mat = nullptr) {
                material = mat;
            }

            /// @brief Mono material to render the scene with.
            REFLECT_FIELD(Material*, material)

            virtual void Render() override {
                RenderFeature::Render();

                if (material == nullptr) {
                    throw("CondorEngine::Rendering::MonoRenderFeature :: Failed to render: No mono material set.");
                }
                // specify which shader to use
                glUseProgram(material->getShader().program);

                for (Mesh* mesh : Renderer::meshes) {
                    if (mesh->meshData == nullptr) { continue; }
                    // filter to only render enabled layer
                    if (!mesh->getSceneObject()->layer.value & Camera::Main()->layerMask.value) { continue; }

                    // prep shader
                    material->setTransform(mesh->getSceneObject()->getTransform());
                    material->UpdateMat(Camera::Main());

                    // specify which geometry
                    glBindVertexArray(mesh->meshData->getData().vao);
                    // draw the geometry with the shader
                    glDrawElements(GL_TRIANGLES, mesh->meshData->getData().size, GL_UNSIGNED_INT, nullptr);
                }
            }
        };
    }
}
