#include "math.h"
#include "debug.hpp"
//std
#include <cmath>

const float CondorEngine::Math::PI = 3.14159265358979323846264338327950288f;

#pragma region Transform Values

CondorEngine::Vector3 CondorEngine::Math::getTransformAxis(Transform transform, Axis axis)
{
    return transform[axis];
}

CondorEngine::Vector3 CondorEngine::Math::getTransformEulerRotation(Transform transform)
{
    return glm::eulerAngles(glm::quat_cast(transform));
}

CondorEngine::Vector3 CondorEngine::Math::getTransformPosition(Transform transform)
{
    return Vector3(transform[3]);
}

CondorEngine::Transform CondorEngine::Math::setTransformPosition(Transform transform, Vector3 position)
{
    transform[3] = Vector4(position, transform[3].w);
    return transform;
}

CondorEngine::Quaternion CondorEngine::Math::getTransformRotation(Transform transform)
{
    return glm::quat_cast(transform);
}

CondorEngine::Transform CondorEngine::Math::setTransformRotation(Transform transform, Quaternion rotation)
{
    Transform t = glm::mat4_cast(rotation);
    t = glm::scale(t, getTransformScale(transform));
    t[3] = transform[3];
    return t;
}

CondorEngine::Vector3 CondorEngine::Math::getTransformScale(Transform transform)
{
    return Vector3{
        glm::length(Vector3{ transform[0] }),
        glm::length(Vector3{ transform[1] }),
        glm::length(Vector3{ transform[2] })
    };
}

void CondorEngine::Math::getTransformSplit(Transform transform, Vector3 &position, Quaternion &rotation, Vector3 &scale)
{
    position = getTransformPosition(transform);
    rotation = getTransformRotation(transform);
    scale = getTransformScale(transform);
}

CondorEngine::Vector3 CondorEngine::Math::getTransformVector(Transform transform, Vector3 vector)
{
    Vector3 pos; Quaternion rotation; Vector3 scale;
    Math::getTransformSplit(transform, pos, rotation, scale);
    Vector4 out = rotation * Vector4{ vector.x, vector.y, vector.z, 1 };
    return Vector3{ out.x, out.y, out.z };
}

#pragma endregion

CondorEngine::Transform CondorEngine::Math::TransformRotate(Transform transform, Vector3 vector)
{
    return glm::rotate(transform, glm::radians(glm::length(vector)), glm::normalize(vector));
}

CondorEngine::Transform CondorEngine::Math::TransformTranslate(Transform transform, Vector3 vector)
{
    transform[3].x += vector.x;
    transform[3].y += vector.y;
    transform[3].z += vector.z;
    return transform;
}

#pragma region to_string

std::string CondorEngine::to_string(glm::vec2 value)
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

std::string CondorEngine::to_string(glm::vec4 value)
{
    return std::string(
        "(" +
        std::to_string(value.x) + ", " +
        std::to_string(value.y) + ", " +
        std::to_string(value.z) + ", " +
        std::to_string(value.w) + ")"
    );
}

std::string CondorEngine::to_string(glm::quat value)
{
    return std::string(
        "(" +
        std::to_string(value.w) + ", " +
        std::to_string(value.x) + ", " +
        std::to_string(value.y) + ", " +
        std::to_string(value.z) + ")"
    );
}

std::string CondorEngine::to_string(glm::mat4 value, bool multiline)
{
    return std::string((multiline ? "\n[(xx:" : "[(xx:") +
        std::to_string(value[0][0]) + ", yx:" + std::to_string(value[1][0]) + ", zx:" + std::to_string(value[2][0]) + ", px:" + std::to_string(value[3][0]) + ")" + (multiline ? "]\n[" : ", ") +
        "(xy:" + std::to_string(value[0][1]) + ", yy:" + std::to_string(value[1][1]) + ", zy:" + std::to_string(value[2][1]) + ", py:" + std::to_string(value[3][1]) + ")" + (multiline ? "]\n[" : ", ") +
        "(xz:" + std::to_string(value[0][2]) + ", yz:" + std::to_string(value[1][2]) + ", zz:" + std::to_string(value[2][2]) + ", pz:" + std::to_string(value[3][2]) + ")" + (multiline ? "]\n[" : ", ") +
        "(xw:" + std::to_string(value[0][3]) + ", yw:" + std::to_string(value[1][3]) + ", zw:" + std::to_string(value[2][3]) + ", pw:" + std::to_string(value[3][3]) + ")]"
    );
}

#pragma endregion
