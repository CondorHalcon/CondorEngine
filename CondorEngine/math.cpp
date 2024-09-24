#include "math.h"
#include "debug.h"
#include "core.h"
//std
#include <cmath>
#include <string>
// third party
#include "glm/ext.hpp"
#define GLM_ENABLE_EXPERIMENTAL
#include "glm/gtx/matrix_decompose.hpp"


CondorEngine::Vector3 CondorEngine::Math::TransformVector(Transform transform, Vector3 vector)
{
    Vector3 pos; Quaternion rotation; Vector3 scale;
    Math::TransformSplit(transform, pos, rotation, scale);
    Vector4 out = rotation * Vector4{ vector.x, vector.y, vector.z, 1 };
    return Vector3{ out.x, out.y, out.z };
}

CondorEngine::Vector3 CondorEngine::Math::TransformAxis(Transform transform, Axis axis)
{
    return glm::normalize(Vector3(transform[axis]));
}

CondorEngine::Vector3 CondorEngine::Math::TransformPosition(Transform transform)
{
    return glm::normalize(Vector3(transform[3]));
}

CondorEngine::Transform CondorEngine::Math::TransformRotate(Transform transform, Vector3 vector)
{
    return glm::rotate(transform, glm::radians(glm::length(vector)), glm::normalize(vector));
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

CondorEngine::String CondorEngine::to_string(CondorEngine::Vector2 value)
{
    return String(
        "(" +
        std::to_string(value.x) + "," +
        std::to_string(value.y) + ")"
    );
}

CondorEngine::String CondorEngine::to_string(glm::vec3 value)
{
    return String(
        "(" +
        std::to_string(value.x) + ", " +
        std::to_string(value.y) + ", " +
        std::to_string(value.z) + ")"
    );
}

CondorEngine::String CondorEngine::to_string(CondorEngine::Vector4 value)
{
    return String(
        "(" +
        std::to_string(value.x) + ", " +
        std::to_string(value.y) + ", " +
        std::to_string(value.z) + ", " +
        std::to_string(value.w) + ")"
    );
}

CondorEngine::String CondorEngine::to_string(CondorEngine::Quaternion value)
{
    return String(
        "(" +
        std::to_string(value.w) + ", " +
        std::to_string(value.x) + ", " +
        std::to_string(value.y) + ", " +
        std::to_string(value.z) + ")"
    );
}

#pragma endregion
