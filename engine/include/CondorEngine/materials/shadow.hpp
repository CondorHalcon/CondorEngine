#pragma once
#include "CondorEngine/pch.h"
#include "CondorEngine/material.h"
#include "CondorEngine/resourcemanager.h"
#include "CondorEngine/components/camera.h"

namespace CondorEngine
{
    namespace Rendering
    {
        class Shadow : public Material
        {
        public:
            Shadow() : Material(ResourceManager::LoadShader("CondorEngine/shaders/directional.vert", "CondorEngine/shaders/shadow.frag")) {}

            virtual void Update() override {
                Transform lightProjection = glm::ortho(-10.0f, 10.0f, -10.0f, 10.0f, 1.0f, 10.5f);
                Transform lightView = glm::lookAt(
                    glm::vec3(0.0, 10.0, 0.0), // light position
                    glm::vec3(0.0f, -1.0, 0.0f), // look at position
                    glm::vec3(0.0f, 1.0f, 0.0f) // up vector
                );
                if (Camera::Main() != nullptr) {
                    lightProjection = Camera::Main()->getSunProjectionMatrix();
                    lightView = Camera::Main()->getSunViewMatrix();
                }

                SetUniform(0, lightProjection);
                SetUniform(1, lightView);
                SetUniform(2, transform);
            }
        };
    }
}
