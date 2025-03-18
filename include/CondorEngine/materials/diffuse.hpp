#pragma once
#include "CondorEngine/pch.h"
#include "CondorEngine/material.h"
// internal
#include "CondorEngine/application.h"
#include "CondorEngine/components/camera.h"
#include "CondorEngine/components/light.h"
#include "CondorEngine/resourcemanager.h"

namespace CondorEngine
{
    /// @brief Diffuse lighting material.
    class Diffuse : public Material
    {
    public:
        /// @brief Albedo texture.
        Texture texture;
        /// @brief Albedo tint.
        ColorRGB tint;

    private:
        unsigned int textureUniform;
        unsigned int tintUniform;

    public:
        /// @brief Class constructor.
        Diffuse() : Material(ResourceManager::LoadShader("shaders/directional.vert", "shaders/diffuse.frag")) {
            this->texture = ResourceManager::LoadTexture("textures/PBRBlank/PBRB_Albedo.png");
            this->tint = ColorRGB(1, 1, 1);

            textureUniform = GetUniformLocation("material.texture");
            tintUniform = GetUniformLocation("material.tint");
        }

        /// @brief Class constructor.
        /// @param texture Albedo texture.
        Diffuse(Texture tex) : Diffuse() { texture = tex; }

        /// @brief Update shader uniforms.
        virtual void Update() override {
            Material::Update();
            // lighting
            if (Application::activeScene != nullptr) {
                SetUniform(3, Application::activeScene->ambientLight);
                SetUniform(4, Application::activeScene->light->color);
                SetUniform(5, Application::activeScene->light->direction);
            }
            else {
                SetUniform(3, ColorRGB{ .5f, .5f, .5f });
                SetUniform(4, ColorRGB{ .5f, .5f, .5f });
                SetUniform(5, Vector3{ .3f, .3f, .3f });
            }
            // material values
            SetUniform(textureUniform, texture, 0);
            SetUniform(tintUniform, tint);
        }
    };
}