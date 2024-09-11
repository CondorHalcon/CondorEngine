#pragma once

// std
#include <string>
using std::string;
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
    static Transform EulerToTransform(Vector3 vector);
    static Vector3 TransformToPosition(Transform transform);
    static Vector3 TransformToEulerRotation(Transform transform);
};

#pragma region Utilities

string to_string(Color color);
string to_string(ColorRGB color);
string to_string(Vector2 vector);
string to_string(Vector3 vector);
string to_string(Vector4 vector);
string to_string(Quaternion quaternion);
string to_string(Transform transfrom);

#pragma endregion

}

