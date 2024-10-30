#pragma once
// internal
#include "math.h"
#include "renderer.h"
#include "object.h"
// third party
#include "glew/glew.h"

namespace CondorEngine
{
    /// @brief Mesh material class.
	class Material : public Object {
	public:
		/// @brief Class constructor.
		/// @param shader Material shader.
		Material(Shader* shader);
		/// @brief Class deconstructor.
		~Material();
		/// @brief Update material.
		void Update() override;
	protected:
		/// @brief Material Shader reference.
		Shader* shader;
		/// @brief Model transform matrix.
		Transform transform;
	public:
		/// @brief Set material shader.
		/// @param shader Shader to set.
		void setShader(Shader* shader);
		/// @brief Get material Shader.
		/// @return Material Shader.
		Shader* getShader();
		/// @brief Set model transform matrix.
		/// @param transform Model transform matrix.
		void setTransform(Transform transform);
	protected:
		/// @brief Get the location of a uniform.
		/// @param name Name of the uniform.
		/// @return Uniform location.
		int GetUniformLocation(const char* name);
		/// @brief Set shader uniforms for `Transform`.
		/// @param location Shader layout location.
		/// @param value Uniform value.
		void SetUniform(GLuint location, const Transform& value); // for transforms
		/// @brief Set shader uniforms for `Texture`.
		/// @param location Shader layout location.
		/// @param value Uniform value.
		/// @param textureSlot
		void SetUniform(GLuint location, const Texture& value, int textureSlot); // for textures
		/// @brief Set Shader uniforms for `Vector3` and `ColorRGB`.
		/// @param location Shader layout location.
		/// @param value Uniform value.
		void SetUniform(GLuint location, const glm::vec3& value); // for rgb color & positions
		/// @brief Set shader uniform for `Vector4` and `Color`.
		/// @param location Shader layout location.
		/// @param value Uniform value.
		void SetUniform(GLuint location, const glm::vec4& value); // for color and quaternions
		/// @brief Set Shader uniforms for `Vector3` and `ColorRGB` arrays.
		/// @param location Shader layout location.
		/// @param count Length of array
		/// @param values Uniform value.
		void SetUniform(GLuint location, int count, const glm::vec3 &values);
	};

#pragma region Preset Materials
	/// @brief Unlit material.
	class M_Unlit : public Material {
	public:
		/// @brief Class constructor.
        M_Unlit();
		/// @brief Class constructor.
		/// @param texture Albedo texture.
		M_Unlit(Texture* texture);
        /// @brief Update shader uniforms.
        void Update() override;
        /// @brief Albedo texture.
		Texture* texture;
		/// @brief Cleanly set or change the albedo texture.
		/// @param texture New albedo texture.
		void setTexture(Texture* texture);
	};
	/// @brief Simple lit material.
	class M_Lit : public Material {
	protected:
		/// @brief Class constructor
		/// @param shader Shader this material will use.
        M_Lit(Shader *shader);
    public:
		/// @brief Class constructor.
        M_Lit();
		/// @brief Class constructor.
		/// @param texture Albedo texture.
		M_Lit(Texture* texture);
        /// @brief Update shader uniforms.
        void Update() override;
        /// @brief Albedo texture.
		Texture* texture;
		/// @brief Cleanly set or change the albedo texture.
		/// @param texture New albedo texture.
		void setTexture(Texture* texture);
	};
	/// @brief Multi-light lit material.
	class M_ComplexLit : public M_Lit {
	public:
		/// @brief Maximum number of lights.
		static const int MAX_LIGHTS = 2;
		/// @brief Class constructor.
        M_ComplexLit();
        /// @brief Update shader uniforms.
        void Update() override;
    };
	/// @brief UV material.
	class M_UV : public Material {
	public:
		/// @brief Class constructor.
        M_UV();
    };
	/// @brief Object normal material.
	class M_Normal : public Material {
	public:
		/// @brief Class constructor.
        M_Normal();
    };
	/// @brief Screen space normal material.
	class M_ScreenNormal : public Material {
	public:
		/// @brief Class constructor.
        M_ScreenNormal();
    };
#pragma endregion
}
