#pragma once
#include "CondorEngine/pch.h"
#include "CondorEngine/material.h"
#include "CondorEngine/resourcemanager.h"

namespace CondorEngine
{
    /// @brief Unlit material.
    class Unlit : public Material
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
        Unlit() : Material(ResourceManager::LoadShader("shaders/directional.vert", "shaders/unlit.frag")) {
            this->name = "CondorEngine::Unlit";
            this->texture = ResourceManager::LoadTexture("textures/PBRBlank/PBRB_Albedo.png");
            this->tint = ColorRGB(1, 1, 1);

            textureUniform = GetUniformLocation("material.texture");
            tintUniform = GetUniformLocation("material.tint");
        }

        /// @brief Class constructor.
        /// @param texture Albedo texture.
        Unlit(Texture tex) : Unlit() { setTexture(tex); }

        /// @brief Update shader uniforms.
        virtual void Update() override {
            Material::Update();
            // material values
            SetUniform(textureUniform, texture, 0);
            SetUniform(tintUniform, tint);
        }

        /// @brief Cleanly set or change the albedo texture.
        /// @param texture New albedo texture.
        void setTexture(Texture tex) {
            this->texture = tex;
        }
    };
}
