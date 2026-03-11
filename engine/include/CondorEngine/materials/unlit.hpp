#pragma once
#include "CondorEngine/pch.h"
#include "CondorEngine/material.h"
#include "CondorEngine/resourcemanager.h"

namespace CondorEngine
{
    /// @brief Unlit material.
    class Unlit : public Material
    {
        REFLECT_CLASS(CondorEngine::Unlit, Material)
    public:
        /// @brief Albedo texture.
        Resource<Texture>* texture = nullptr;
        /// @brief Albedo tint.
        ColorRGB tint;

    private:
        unsigned int textureUniform;
        unsigned int tintUniform;

    public:
        /// @brief Class constructor.
        Unlit(Resource<Texture>* tex) : Material("Unlit", ResourceManager::LoadShader("CondorEngine/shaders/directional.vert", "CondorEngine/shaders/unlit.frag")) {
            this->texture = tex;
            this->tint = ColorRGB(1, 1, 1);

            textureUniform = GetUniformLocation("material.texture");
            tintUniform = GetUniformLocation("material.tint");
        }

        /// @brief Default lass constructor.
        /// @param texture Albedo texture.
        Unlit() : Unlit(ResourceManager::LoadTexture("CondorEngine/textures/PBRBlank/PBRB_Albedo.png")) {}

        /// @brief Update shader uniforms.
        virtual void UpdateMat(Camera* cam) override {
            Material::UpdateMat(cam);
            // material values
            SetUniform(textureUniform, texture->getData(), 0);
            SetUniform(tintUniform, tint);
        }

        /// @brief Cleanly set or change the albedo texture.
        /// @param texture New albedo texture.
        void setTexture(Resource<Texture>* tex) {
            this->texture = tex;
        }
    };
}
