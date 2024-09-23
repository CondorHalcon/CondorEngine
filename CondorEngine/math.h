#pragma once

// std
#include <string>
// third party
#include "glm/ext.hpp"

namespace CondorEngine {

#pragma region Types

	/// <summary> RGBA values for color. (Abstract of glm::vec4) </summary>
	typedef glm::vec4 Color;
	/// <summary> RGB values for color. (Abstract of glm::vec3) </summary>
	typedef glm::vec3 ColorRGB;
	/// <summary> 2 dimensional vector. (Abstract of glm::vec2) </summary>
	typedef glm::vec2 Vector2;
	/// <summary> 2 dimensional integer vector. (Abstract of glm::ivec2) </summary>
	typedef glm::ivec2 Vector2Int;
	/// <summary> 3 dimensional vector. (Abstract of glm::vec3) </summary>
	typedef glm::vec3 Vector3;
	/// <summary> 3 dimensional integer vector. (Abstract of glm::ivec3) </summary>
	typedef glm::ivec3 Vector3Int;
	/// <summary> 4 dimensional vector. (Abstract of glm::vec4) </summary>
	typedef glm::vec4 Vector4;
	/// <summary> 4 dimensional integer vector. (Abstract of glm::ivec4) </summary>
	typedef glm::ivec4 Vector4Int;
	/// <summary> Rotational information. (Abstract of glm::vec4) </summary>
	typedef glm::quat Quaternion;
	/// <summary> Transformation matrix 4x4. (Abstract of glm::mat4) </summary>
	typedef glm::mat4 Transform;

#pragma endregion

class Math
{
public:
	/// <summary> Transform vector from local space to world space. </summary>
	static Vector3 TransformVector(Transform transform, Vector3 vector);
	static Vector3 TransformForward(Transform transform);
	static Vector3 TransformRight(Transform transform);
	static Transform TransformRotate(Transform transform, Vector3 vector);
	static void TransformSplit(Transform transform, Vector3& position, Quaternion& rotation, Vector3& scale);
	static Transform TransformTranslate(Transform transform, Vector3 vector);
	static Vector3 TransformUp(Transform transform);
};

#pragma region Utilities

std::string to_string(CondorEngine::Vector2 vector);
std::string to_string(CondorEngine::Vector3 vector);
std::string to_string(CondorEngine::Vector4 vector);
std::string to_string(CondorEngine::Transform transform);

#pragma endregion

}