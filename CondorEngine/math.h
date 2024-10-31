#pragma once
// std
#include <string>
// third party
#include "glm/ext.hpp"

namespace CondorEngine {

#pragma region GLM Types

	
	/// @brief RGBA values for color. (Abstract of glm::vec4)
	typedef glm::vec4 Color;
	/// @brief RGB values for color. (Abstract of glm::vec3)
	typedef glm::vec3 ColorRGB;
	/// @brief 2 dimensional vector. (Abstract of glm::vec2)
	typedef glm::vec2 Vector2;
	/// @brief 2 dimensional integer vector. (Abstract of glm::ivec2)
	typedef glm::ivec2 Vector2Int;
	/// @brief 3 dimensional vector. (Abstract of glm::vec3)
	typedef glm::vec3 Vector3;
	/// @brief 3 dimensional integer vector. (Abstract of glm::ivec3)
	typedef glm::ivec3 Vector3Int;
	/// @brief 4 dimensional vector. (Abstract of glm::vec4)
	typedef glm::vec4 Vector4;
	/// @brief 4 dimensional integer vector. (Abstract of glm::ivec4)
	typedef glm::ivec4 Vector4Int;
	/// @brief Rotational information. (Abstract of glm::vec4)
	typedef glm::quat Quaternion;
	/// @brief Transformation matrix 4x4. (Abstract of glm::mat4)
	typedef glm::mat4 Transform;

#pragma endregion

#pragma region Enums

	enum Axis
	{
		Right = 0,
		Up = 1,
		Forward = 2
	};

#pragma endregion

#pragma region Math

	/// @brief Math utility class.
	class Math
	{
	public:
		/// @brief Good old PI (3.14)
		const static float PI;

	public:
#pragma region Transform Get/Set
		/// @brief Get transform rotation axis.
		/// @param transform Transform matrix.
		/// @param axis Axis to get.
		/// @return Axis direction.
		static Vector3 getTransformAxis(Transform transform, Axis axis);
		/// @brief Get transform euler rotation.
		/// @param transform Transform matrix.
		/// @return Vector3 euler rotation.
		static Vector3 getTransformEulerRotation(Transform transform);
		/// @brief Get transform position.
		/// @param transform Transform matrix.
		/// @return Vector3 position.
		static Vector3 getTransformPosition(Transform transform);
		/// @brief Set transform position.
		/// @param transform Original transform matrix.
		/// @param position Vector3 position.
		/// @return New transform matrix.
		static Transform setTransformPosition(Transform transform, Vector3 position);
		/// @brief Get transform rotation.
		/// @param transform Transform matrix.
		/// @return Quaternion rotation.
		static Quaternion getTransformRotation(Transform transform);
		/// @brief Set transform rotation.
		/// @param transform Original transform matrix.
		/// @param rotation Quaternion rotation.
		/// @return New transform matrix.
		static Transform setTransformRotation(Transform transform, Quaternion rotation);
		/// @brief Get transform scale.
		/// @param transform Transform matrix.
		/// @return Vector3 scale.
		static Vector3 getTransformScale(Transform transform);
		/// @brief Extract the position, rotation, and scale of a transform.
		/// @param transform Transform matrix.
		/// @param position out Transform position.
		/// @param rotation out Transform rotation.
		/// @param scale out Transform scale.
		static void getTransformSplit(Transform transform, Vector3& position, Quaternion& rotation, Vector3& scale);
		/// @brief Transform vector from local space to world space.
		/// @param transform The relative transform matrix.
		/// @param vector The local space vector.
		/// @return Global space vector.
		static Vector3 getTransformVector(Transform transform, Vector3 vector);
#pragma endregion
		
#pragma region Transform Manipulation
		/// @brief Rotate transform with euler angles.
		/// @param transform Transform matrix.
		/// @param vector Euler rotation.
		/// @return Rotated transform matrix.
		static Transform TransformRotate(Transform transform, Vector3 vector);
		/// @brief Translate a transform in global space.
		/// @param transform Transform matrix.
		/// @param vector Translation.
		/// @return Translated transform matrix.
		static Transform TransformTranslate(Transform transform, Vector3 vector);
#pragma endregion
	};

#pragma endregion

#pragma region to_string

	/// @brief String value of a `Vector2`.
	/// @param value 
	/// @return 
	std::string to_string(glm::vec2 value);
	/// @brief String value of a `Vector3` and `ColorRGB`.
	/// @param value 
	/// @return 
	std::string to_string(glm::vec3 value);
	/// @brief String value of a `Vector4` and `Color`.
	/// @param value 
	/// @return 
	std::string to_string(glm::vec4 value);
	/// @brief String value of a `Quaternion`.
	/// @param value 
	/// @return 
	std::string to_string(glm::quat value);
	/// @brief String value of a `Transform`.
	/// @param value 
	/// @return 
	std::string to_string(glm::mat4 value, bool multiline = false);

#pragma endregion

}