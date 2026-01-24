#pragma once
#include "CondorEngine/pch.h"
#include "CondorEngine/rendering/renderfeature.h"
#include "CondorEngine/rendering/renderer.h"
#include "CondorEngine/components/mesh.h"
#include "CondorEngine/material.h"
#include "CondorEngine/sceneobject.h"
#include "CondorEngine/materials/shadow.hpp"
#include "CondorEngine/materials/depth.hpp"
#include "CondorEngine/application.h"

namespace CondorEngine
{
    namespace Rendering
    {
        class DllExport DirectionalShadowMappingRenderFeature : public RenderFeature
        {
        public:
            unsigned int shadowLayer{ 0xF };
            GLuint shadowMapFBO;
            Texture shadowTexture;
            Material* material{ nullptr };
            bool enablePostProcessOverride{ true };

        private:
            static DirectionalShadowMappingRenderFeature* instance;

        public:
            static DirectionalShadowMappingRenderFeature* Instance() {
                if (instance == nullptr) {
                    instance = new DirectionalShadowMappingRenderFeature();
                }
                return instance;
            }
            static bool Exists(DirectionalShadowMappingRenderFeature** srf) {
                *srf = instance;
                if (instance == nullptr) {
                    return false;
                }
                return true;
            }

            virtual void PreProccess() override {
                if (material == nullptr) {
                    throw("CondorEngine::Rendering::DirectionalShadowMappingRenderFeature :: Failed to render: No material set to render feature.");
                }
                // specify which shader to use
                glUseProgram(material->getShader().program);

                glViewport(0, 0, shadowTexture.width, shadowTexture.height);
                glBindFramebuffer(GL_FRAMEBUFFER, shadowMapFBO);
                glClear(GL_DEPTH_BUFFER_BIT);

                for (Mesh* mesh : Renderer::meshes) {
                    // filter to only render enabled layer
                    if (!mesh->getSceneObject()->layer & shadowLayer) { continue; }

                    // prep shader
                    material->setTransform(mesh->getSceneObject()->getTransform());
                    material->Update();

                    // specify which geometry
                    glBindVertexArray(mesh->data.vao);
                    // draw the geometry with the shader
                    glDrawElements(GL_TRIANGLES, mesh->data.size, GL_UNSIGNED_INT, nullptr);
                }
            }

            virtual void PostProcess() {
                if (!enablePostProcessOverride) { return; }

                // bind read and write framebuffers
                glBindFramebuffer(GL_READ_FRAMEBUFFER, shadowMapFBO);
                glBindFramebuffer(GL_DRAW_FRAMEBUFFER, 0);

                // blit (copy) framebuffer
                Vector2Int window = Application::Instance()->getWindowDimensions();
                glBlitFramebuffer(
                    0, 0, shadowTexture.width, shadowTexture.height,
                    0, 0, window.x, window.y,
                    GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT,
                    GL_NEAREST);
            }

        private:
            DirectionalShadowMappingRenderFeature() {
                material = new Shadow();

                // create shadow framebuffer
                glGenFramebuffers(1, &shadowMapFBO);

                // create shadow texture
                shadowTexture = Texture();
                shadowTexture.width = shadowTexture.height = 1024;
                glGenTextures(1, &shadowTexture.handle);
                glBindTexture(GL_TEXTURE_2D, shadowTexture.handle);
                glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT, shadowTexture.width, shadowTexture.height, 0, GL_DEPTH_COMPONENT, GL_FLOAT, NULL);
                glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
                glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
                glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
                glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

                // attach shadow texture to framebuffer's depth buffer
                glBindFramebuffer(GL_FRAMEBUFFER, shadowMapFBO);
                glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D, shadowTexture.handle, 0);
                glDrawBuffer(GL_NONE);
                glReadBuffer(GL_NONE);
                glBindFramebuffer(GL_FRAMEBUFFER, 0);
            }

            ~DirectionalShadowMappingRenderFeature() {
                if (instance == this) { instance = nullptr; }
                glDeleteFramebuffers(1, &shadowMapFBO);
                Texture::FreeTexture(shadowTexture);
            }
        };
    }
}