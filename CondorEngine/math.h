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
	/// <summary> 3 dimensional vector. (Abstract of glm::vec3) </summary>
	typedef glm::vec3 Vector3;
	/// <summary> 4 dimensional vector. (Abstract of glm::vec4) </summary>
	typedef glm::vec4 Vector4;
	/// <summary> Rotational information. (Abstract of glm::vec4) </summary>
	typedef glm::vec4 Quaternion;
	/// <summary> Transformation matrix 4x4. (Abstract of glm::mat4) </summary>
	typedef glm::mat4 Transform;

#pragma endregion

class Math
{
public:
	static Transform TransformSetPosition(Transform transform, Vector3 position);
    static Vector3 TransformToPosition(Transform transform);
};

}

#pragma region Utilities

std::string to_string(CondorEngine::Color color);
std::string to_string(CondorEngine::ColorRGB color);
std::string to_string(CondorEngine::Vector2 vector);
std::string to_string(CondorEngine::Vector3 vector);
std::string to_string(CondorEngine::Vector4 vector);
std::string to_string(CondorEngine::Quaternion quaternion);
std::string to_string(CondorEngine::Transform transform);

#pragma endregion
