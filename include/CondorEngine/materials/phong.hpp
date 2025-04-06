#pragma once
#include "CondorEngine/pch.h"
#include "CondorEngine/material.h"
// std
#include <climits>
// internal
#include "CondorEngine/application.h"
#include "CondorEngine/components/camera.h"
#include "CondorEngine/components/light.h"
#include "CondorEngine/rendering/renderer.h"
#include "CondorEngine/resourcemanager.h"
#include "CondorEngine/rendering/renderfeatures/directionalshadowmappingrenderfeature.hpp"
#include "CondorEngine/scene.h"

namespace CondorEngine
{
    /// @brief Phong lighting material
    class Phong : public Material
    {
    public:
        /// @brief Maximum number of lights.
        static const int MAX_LIGHTS = 2;

        /// @brief Albedo texture.
        Texture texture;
        /// @brief Color tint.
        ColorRGB tint;
        /// @brief Specular texture.
        Texture specular;
        /// @brief Specular multiplayer.
        float specularMul;
        /// @brief Specular smoothness texture.
        Texture smoothness;
        /// @brief Specular smoothness multiplayer.
        float smoothnessMul;
        Texture shadowMap;

    private:
        unsigned int textureUniform;
        unsigned int tintUniform;
        unsigned int specularUniform;
        unsigned int specularMulUniform;
        unsigned int smoothnessUniform;
        unsigned int smoothnessMulUniform;
        struct LightUniforms
        {
            unsigned int position{ UINT32_MAX };
            unsigned int direction{ UINT32_MAX };
            unsigned int color{ UINT32_MAX };
            unsigned int cutoff{ UINT32_MAX };
            unsigned int outerCutoff{ UINT32_MAX };
        } lightUniforms[MAX_LIGHTS];
        unsigned int shadowMapUniform{ UINT32_MAX };

    public:
        /// @brief Class constructor.
        Phong() : Material(ResourceManager::LoadShader("shaders/directional.vert", "shaders/phong.frag")) {
            this->name = "CondorEngine::Phong";
            texture = ResourceManager::LoadTexture("textures/PBRBlank/PBRB_Albedo.png");
            tint = ColorRGB(1, 1, 1);
            specular = ResourceManager::LoadTexture("textures/PBRBlank/PBRB_Gloss.png");
            specularMul = 1;
            smoothness = ResourceManager::LoadTexture("textures/PBRBlank/PBRB_Gloss.png");
            smoothnessMul = 1;

            Rendering::DirectionalShadowMappingRenderFeature* shadowRF = nullptr;
            if (Rendering::DirectionalShadowMappingRenderFeature::Exists(&shadowRF)) {
                this->shadowMap = shadowRF->shadowTexture;
            }
            else {
                this->shadowMap = ResourceManager::LoadTexture("textures/PBRBlank/PBRB_Albedo.png");
            }

            textureUniform = GetUniformLocation("material.texture");
            tintUniform = GetUniformLocation("material.tint");
            specularUniform = GetUniformLocation("material.specular");
            specularMulUniform = GetUniformLocation("material.specularMul");
            smoothnessUniform = GetUniformLocation("material.smoothness");
            smoothnessMulUniform = GetUniformLocation("material.smoothnessMul");
            shadowMapUniform = GetUniformLocation("shadowMap");
            for (int i = 0; i < MAX_LIGHTS; i++) {
                std::string light = std::string("lights[") + std::to_string(i) + std::string("]");
                lightUniforms[i].position = GetUniformLocation((light + std::string(".position")).c_str());
                lightUniforms[i].direction = GetUniformLocation((light + std::string(".direction")).c_str());
                lightUniforms[i].color = GetUniformLocation((light + std::string(".color")).c_str());
                lightUniforms[i].cutoff = GetUniformLocation((light + std::string(".cutoff")).c_str());
                lightUniforms[i].outerCutoff = GetUniformLocation((light + std::string(".outerCutoff")).c_str());
            }
        }

        /// @brief Class constructor.
        /// @param texture Albedo texture.
        Phong(Texture tex) : Phong() { texture = tex; }

        /// @brief Update shader uniforms.
        virtual void Update() override {
            Material::Update();
            // lighting
            ColorRGB ambientLight = ColorRGB{ .3f, .3f, .3f };
            ColorRGB sunLight = ColorRGB{ .5f, .5f, .5f };
            ColorRGB sunDirection = Vector3{ 0.f, -1.f, 0.f };

            if (Application::activeScene != nullptr) {
                ambientLight = Application::activeScene->ambientLight;
                sunLight = Application::activeScene->light.color;
                sunDirection = Application::activeScene->light.direction;
                // scene lights
                for (int i = 0; i < MAX_LIGHTS; i++) {
                    if (i < Rendering::Renderer::lights.size()) {
                        SetUniform(lightUniforms[i].position, Rendering::Renderer::lights[i]->getLightPosition());
                        SetUniform(lightUniforms[i].direction, Rendering::Renderer::lights[i]->getLightColor());
                        SetUniform(lightUniforms[i].color, Rendering::Renderer::lights[i]->getLightColor());
                        SetUniform(lightUniforms[i].cutoff, Rendering::Renderer::lights[i]->getLightCutoff());
                        SetUniform(lightUniforms[i].outerCutoff, Rendering::Renderer::lights[i]->getLightOuterCutoff());
                    }
                    else {
                        SetUniform(lightUniforms[i].position, Vector3{ 0,0,0 });
                        SetUniform(lightUniforms[i].direction, Vector3{ 0,-1,0 });
                        SetUniform(lightUniforms[i].color, Vector3{ 0,0,0 });
                        SetUniform(lightUniforms[i].cutoff, 360);
                        SetUniform(lightUniforms[i].outerCutoff, 360);
                    }
                }
            }
            else {
                // scene lights
                for (int i = 0; i < MAX_LIGHTS; i++) {
                    SetUniform(lightUniforms[i].position, Vector3{ 0,0,0 });
                    SetUniform(lightUniforms[i].direction, Vector3{ 0,-1,0 });
                    SetUniform(lightUniforms[i].color, Vector3{ 0,0,0 });
                    SetUniform(lightUniforms[i].cutoff, 360);
                    SetUniform(lightUniforms[i].outerCutoff, 360);
                }
            }
            // camera position
            if (Camera::Main() != nullptr) {
                SetUniform(7, Camera::Main()->getPosition());
            }
            else {
                SetUniform(7, Vector3{ 0, 0, 0 });
            }
            // sun and ambient light
            SetUniform(4, ambientLight);
            SetUniform(5, sunLight);
            SetUniform(6, sunDirection);
            SetUniform(shadowMapUniform, shadowMap, 3);
            // material values
            SetUniform(textureUniform, texture, 0);
            SetUniform(tintUniform, tint);
            SetUniform(specularUniform, specular, 1);
            SetUniform(specularMulUniform, specularMul);
            SetUniform(smoothnessUniform, smoothness, 2);
            SetUniform(smoothnessMulUniform, smoothnessMul);
        }
    };
}
