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
    /// @brief Phong lighting material
    class Phong : public Material
    {
    public:
        /// @brief Albedo texture.
        Texture texture;
        /// @brief Color tint.
        ColorRGB tint;
        /// @brief Specular strength.
        float specular;
        /// @brief Specular smoothness.
        float smoothness;

    private:
        unsigned int textureUniform;
        unsigned int tintUniform;
        unsigned int specularUniform;
        unsigned int smoothnessUniform;

    protected:
        /// @brief Class constructor
        /// @param shader Shader this material will use.
        Phong(Shader shader) : Material(shader) {
            texture = ResourceManager::LoadTexture("textures/Blank.png");
            tint = ColorRGB(1, 1, 1);
            specular = .5f;
            smoothness = .5f;

            textureUniform = GetUniformLocation("material.texture");
            tintUniform = GetUniformLocation("material.tint");
            specularUniform = GetUniformLocation("material.specular");
            smoothnessUniform = GetUniformLocation("material.smoothness");
        }

    public:
        /// @brief Class constructor.
        Phong() : Phong(ResourceManager::LoadShader("shaders/directional.vert", "shaders/phong.frag")) {}

        /// @brief Class constructor.
        /// @param texture Albedo texture.
        Phong(Texture tex) : Phong() { texture = tex; }

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
            // camera position
            if (Camera::Main() != nullptr) {
                SetUniform(6, Camera::Main()->getPosition());
            }
            else {
                SetUniform(6, Vector3{ 0, 0, 0 });
            }
            // material values
            SetUniform(textureUniform, texture, 0);
            SetUniform(tintUniform, tint);
            SetUniform(specularUniform, specular);
            SetUniform(smoothnessUniform, smoothness);
        }
    };

    class PhongMultiLight : public Phong
    {
    public:
        /// @brief Maximum number of lights.
        static const int MAX_LIGHTS = 2;

        /// @brief Class constructor.
        PhongMultiLight() : Phong(ResourceManager::LoadShader("shaders/directional.vert", "shaders/phong_multi-light.frag")) {}

        /// @brief Class constructor.
        PhongMultiLight(Texture tex) : PhongMultiLight() { texture = tex; }

        /// @brief Update shader uniforms.
        virtual void Update() override {
            Material::Update();
            // lighting
            ColorRGB lightColors[MAX_LIGHTS];
            Vector3 lightDirections[MAX_LIGHTS];
            if (Application::activeScene != nullptr) {
                lightColors[0] = Application::activeScene->light->color;
                lightDirections[0] = Application::activeScene->light->direction;
                for (int i = 0; i < MAX_LIGHTS - 1; i++) {
                    if (i < Application::activeScene->sceneLights.size()) {
                        lightColors[i + 1] = Application::activeScene->sceneLights[i]->getLightColor();
                        lightDirections[i + 1] = Application::activeScene->sceneLights[i]->getLightDirection();
                    }
                    else {
                        lightColors[i + 1] = ColorRGB{ 0, 0, 0 };
                        lightDirections[i + 1] = Vector3{ 1, 0, 0 };
                    }
                }
            }
            else {
                for (int i = 0; i < MAX_LIGHTS; i++) {
                    lightColors[i] = ColorRGB{ .04, .04, 0 };
                    lightDirections[i] = Vector3{ 1, 0, 0 };
                }
            }
            SetUniform(GetUniformLocation("lightColor"), MAX_LIGHTS, *lightColors);
            SetUniform(GetUniformLocation("lightDirection"), MAX_LIGHTS, *lightDirections);
            // camera position
            if (Camera::Main() != nullptr) {
                SetUniform(4, Camera::Main()->getPosition());
            }
            else {
                SetUniform(4, Vector3{ 0, 0, 0 });
            }
            // texture
            SetUniform(5, texture, 0);
        }
    };
}