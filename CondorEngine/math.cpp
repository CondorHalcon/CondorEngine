#include "math.h"
#include "debug.h"
//std
#include <cmath>
// third party
#define GLM_ENABLE_EXPERIMENTAL
#include "glm/gtx/matrix_decompose.hpp"

const float CondorEngine::Math::PI = 3.14159265358979323846264338327950288f;

CondorEngine::Vector3 CondorEngine::Math::TransformVector(Transform transform, Vector3 vector)
{
    Vector3 pos; Quaternion rotation; Vector3 scale;
    Math::TransformSplit(transform, pos, rotation, scale);
    Vector4 out = rotation * Vector4{ vector.x, vector.y, vector.z, 1 };
    return Vector3{ out.x, out.y, out.z };
}

CondorEngine::Vector3 CondorEngine::Math::TransformAxis(Transform transform, Axis axis)
{
    switch (axis)
    {
    case Axis::Right:
        return glm::normalize(TransformVector(transform, Vector3{1, 0, 0}));
    case Axis::Up:
        return glm::normalize(TransformVector(transform, Vector3{0, 1, 0}));
    default:
        return glm::normalize(TransformVector(transform, Vector3{0, 0, 1}));
    }

    // TODO FIX: should work but broken
    return glm::normalize(Vector3(transform[axis]));
}

CondorEngine::Vector3 CondorEngine::Math::TransformPosition(Transform transform)
{
    Vector3 pos; Quaternion rotation; Vector3 scale;
    Math::TransformSplit(transform, pos, rotation, scale);
    return pos;

    // TODO FIX: should work but broken
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

std::string CondorEngine::to_string(CondorEngine::Vector2 value)
{
    return std::string(
        "(" +
        std::to_string(value.x) + "," +
        std::to_string(value.y) + ")"
    );
}

std::string CondorEngine::to_string(glm::vec3 value)
{
    return std::string(
        "(" +
        std::to_string(value.x) + ", " +
        std::to_string(value.y) + ", " +
        std::to_string(value.z) + ")"
    );
}

std::string CondorEngine::to_string(CondorEngine::Vector4 value)
{
    return std::string(
        "(" +
        std::to_string(value.x) + ", " +
        std::to_string(value.y) + ", " +
        std::to_string(value.z) + ", " +
        std::to_string(value.w) + ")"
    );
}

std::string CondorEngine::to_string(CondorEngine::Quaternion value)
{
    return std::string(
        "(" +
        std::to_string(value.w) + ", " +
        std::to_string(value.x) + ", " +
        std::to_string(value.y) + ", " +
        std::to_string(value.z) + ")"
    );
}

#pragma endregion
