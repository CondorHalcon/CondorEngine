#pragma once
#include "CondorEngine/pch.h"
// internal
#include "CondorEngine/math.hpp"
#include "CondorEngine/renderer.h"
#include "CondorEngine/object.h"

namespace CondorEngine
{
	/// @brief Mesh material class.
	class DllExport Material : public Object
	{
	public:
		/// @brief Class constructor.
		/// @param shader Material shader.
		Material(Shader shader);
		/// @brief Update material.
		virtual void Update() override;

	protected:
		/// @brief Material Shader reference.
		Shader shader;
		/// @brief Model transform matrix.
		Transform transform;

	public:
		/// @brief Set material shader.
		/// @param shader Shader to set.
		void setShader(Shader shader);
		/// @brief Get material Shader.
		/// @return Material Shader.
		Shader getShader();
		/// @brief Set model transform matrix.
		/// @param transform Model transform matrix.
		void setTransform(Transform transform);

	protected:
		/// @brief Get the location of a uniform.
		/// @param name Name of the uniform.
		/// @return Uniform location.
		unsigned int GetUniformLocation(const char* name);

		/// @brief Set shader uniforms for `float` using layout location.
		/// @param location Shader layout location.
		/// @param value Uniform value.
		void SetUniform(GLuint location, const float& value);

		/// @brief Set shader uniforms for `float` using uniform name.
		/// @param location Shader layout location.
		/// @param value Uniform value.
		void SetUniform(std::string name, const float& value);

		/// @brief Set shader uniforms for `Transform` using layout location.
		/// @param location Shader layout location.
		/// @param value Uniform value.
		void SetUniform(GLuint location, const Transform& value); // for transforms

		/// @brief Set shader uniforms for `Transform` using unform name.
		/// @param name Shader unform name.
		/// @param value Uniform value.
		void SetUniform(std::string name, const Transform& value);

		/// @brief Set shader uniforms for `Texture` using layout location.
		/// @param location Shader layout location.
		/// @param value Uniform value.
		/// @param textureSlot
		void SetUniform(GLuint location, const Texture& value, int textureSlot); // for textures

		/// @brief Set shader uniforms for `Texture` using unform name.
		/// @param name Shader unform name.
		/// @param value Uniform value.
		/// @param textureSlot
		void SetUniform(std::string name, const Texture& value, int textureSlot);

		/// @brief Set Shader uniforms for `Vector3` and `ColorRGB` using layout location.
		/// @param location Shader layout location.
		/// @param value Uniform value.
		void SetUniform(GLuint location, const glm::vec3& value); // for rgb color & positions

		/// @brief Set Shader uniforms for `Vector3` and `ColorRGB` using unform name.
		/// @param name Shader unform name.
		/// @param value Uniform value.
		void SetUniform(std::string name, const glm::vec3& value);

		/// @brief Set shader uniform for `Vector4` and `Color` using layout location.
		/// @param location Shader layout location.
		/// @param value Uniform value.
		void SetUniform(GLuint location, const glm::vec4& value); // for color and quaternions

		/// @brief Set shader uniform for `Vector4` and `Color` using unform name.
		/// @param name Shader unform name.
		/// @param value Uniform value.
		void SetUniform(std::string name, const glm::vec4& value);

		/// @brief Set Shader uniforms for `Vector3` and `ColorRGB` arrays using layout location.
		/// @param location Shader layout location.
		/// @param count Length of array
		/// @param values Uniform value.
		void SetUniform(GLuint location, int count, const glm::vec3& values);

		/// @brief Set Shader uniforms for `Vector3` and `ColorRGB` arrays using unform name.
		/// @param name Shader unform name.
		/// @param count Length of array
		/// @param values Uniform value.
		void SetUniform(std::string name, int count, const glm::vec3& values);
	};
}
