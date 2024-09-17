#include "math.h"
//std
#include <cmath>
#include <string>
// third party
#include "glm/ext.hpp"
#define GLM_ENABLE_EXPERIMENTAL
#include "glm/gtx/matrix_decompose.hpp"

CondorEngine::Vector3 CondorEngine::Math::TransformForward(Transform transform)
{
    Vector3 pos; Quaternion rotation; Vector3 scale;
    Math::TransformSplit(transform, pos, rotation, scale);
    Vector4 out = rotation * Vector4{ 0, 0, 1, 1 };
    return Vector3{ out.x, out.y, out.z };
}

CondorEngine::Transform CondorEngine::Math::TransformRotate(Transform transform, Vector3 vector)
{
    return glm::rotate(transform, glm::radians(glm::length(vector)), vector);
}

void CondorEngine::Math::TransformSplit(Transform transform, Vector3& position, Quaternion& rotation, Vector3& scale)
{
    Vector3 skew = Vector3{};
    Vector4 perspective = Vector4{};
    glm::decompose(transform, scale, rotation, position, skew, perspective);
}

CondorEngine::Transform CondorEngine::Math::TransformTranslate(Transform transform, Vector3 vector)
{
    return glm::translate(transform, vector);
}

#pragma region Utilities

std::string CondorEngine::to_string(CondorEngine::Vector2 vector)
{
    return std::string(
        "(" +
        std::to_string(vector.x) + "," +
        std::to_string(vector.y) + ")"
    );
}

std::string CondorEngine::to_string(CondorEngine::Vector3 vector)
{
    return std::string(
        "(" +
        std::to_string(vector.x) + ", " +
        std::to_string(vector.y) + ", " +
        std::to_string(vector.z) + ")"
    );
}

std::string CondorEngine::to_string(CondorEngine::Vector4 vector)
{
    return std::string(
        "(" +
        std::to_string(vector.x) + ", " +
        std::to_string(vector.y) + ", " +
        std::to_string(vector.z) + ", " +
        std::to_string(vector.w) + ")"
    );
}

std::string CondorEngine::to_string(CondorEngine::Transform transform)
{
    return std::string();
}

#pragma endregion
