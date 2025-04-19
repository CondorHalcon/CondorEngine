#pragma once
#include "CondorEngine/pch.h"
#include "CondorEngine/material.h"
// internal
#include "CondorEngine/application.h"
#include "CondorEngine/components/camera.h"
#include "CondorEngine/components/light.h"
#include "CondorEngine/rendering/renderer.h"
#include "CondorEngine/resourcemanager.h"
#include "CondorEngine/rendering/renderfeatures/directionalshadowmappingrenderfeature.hpp"

namespace CondorEngine
{
    /// @brief Diffuse lighting material.
    class Diffuse : public Material
    {
    public:
        /// @brief Maximum number of lights.
        static const int MAX_LIGHTS = 2;

        /// @brief Albedo texture.
        Texture texture;

        /// @brief Albedo tint.
        ColorRGB tint;

        Texture shadowMap;

    private:
        unsigned int textureUniform;
        unsigned int tintUniform;
        unsigned int shadowMapUniform{ UINT32_MAX };
        struct LightUniforms
        {
            unsigned int position{ UINT32_MAX };
            unsigned int direction{ UINT32_MAX };
            unsigned int color{ UINT32_MAX };
            unsigned int cutoff{ UINT32_MAX };
            unsigned int outerCutoff{ UINT32_MAX };
        } lightUniforms[MAX_LIGHTS];

    public:
        /// @brief Class constructor.
        Diffuse() : Material(ResourceManager::LoadShader("CondorEngine/shaders/directional.vert", "CondorEngine/shaders/diffuse.frag")) {
            this->name = "CondorEngine::Diffuse";
            this->texture = ResourceManager::LoadTexture("CondorEngine/textures/PBRBlank/PBRB_Albedo.png");
            this->tint = ColorRGB(1, 1, 1);

            Rendering::DirectionalShadowMappingRenderFeature* shadowRF = nullptr;
            if (Rendering::DirectionalShadowMappingRenderFeature::Exists(&shadowRF)) {
                this->shadowMap = shadowRF->shadowTexture;
            }
            else {
                this->shadowMap = ResourceManager::LoadTexture("CondorEngine/textures/PBRBlank/PBRB_Albedo.png");
            }

            textureUniform = GetUniformLocation("material.texture");
            tintUniform = GetUniformLocation("material.tint");
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
        Diffuse(Texture tex) : Diffuse() { texture = tex; }

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
            // sun and ambient light
            SetUniform(4, ambientLight);
            SetUniform(5, sunLight);
            SetUniform(6, sunDirection);
            SetUniform(shadowMapUniform, shadowMap, 1);
            // material values
            SetUniform(textureUniform, texture, 0);
            SetUniform(tintUniform, tint);
        }
    };
}