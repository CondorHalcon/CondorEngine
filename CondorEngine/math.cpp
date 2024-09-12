#include "math.h"
//std
#include <cmath>
#include <string>

CondorEngine::Transform CondorEngine::Math::TransformSetPosition(Transform transform, Vector3 position)
{
    //transform[3] = position.x;
    //transform[7] = position.y;
    //transform[11] = position.z;
    return transform;
}

CondorEngine::Vector3 CondorEngine::Math::TransformToPosition(Transform transform)
{
    return Vector3{transform[3], transform[7], transform[11]};
}

#pragma region Utilities

std::string to_string(CondorEngine::Color color)
{
    return std::string(
        "(" +
        std::to_string(color.r) + ", " +
        std::to_string(color.g) + ", " +
        std::to_string(color.b) + ", " +
        std::to_string(color.a) + ")"
    );
}

std::string to_string(CondorEngine::ColorRGB color)
{
    return std::string(
        "(" +
        std::to_string(color.r) + "," +
        std::to_string(color.g) + "," +
        std::to_string(color.b) + ")"
    );
}

std::string to_string(CondorEngine::Vector2 vector)
{
    return std::string(
        "(" +
        std::to_string(vector.x) + "," +
        std::to_string(vector.y) + ")"
    );
}

std::string to_string(CondorEngine::Vector3 vector)
{
    return std::string(
        "(" +
        std::to_string(vector.x) + ", " +
        std::to_string(vector.y) + ", " +
        std::to_string(vector.z) + ")"
    );
}

std::string to_string(CondorEngine::Vector4 vector)
{
    return std::string(
        "(" +
        std::to_string(vector.x) + ", " +
        std::to_string(vector.y) + ", " +
        std::to_string(vector.z) + ", " +
        std::to_string(vector.w) + ")"
    );
}

std::string to_string(CondorEngine::Quaternion quaternion)
{
    return std::string(
        "(" +
        std::to_string(quaternion.w) + ", " +
        std::to_string(quaternion.x) + ", " +
        std::to_string(quaternion.y) + ", " +
        std::to_string(quaternion.z) + ")"
    );
}

std::string to_string(CondorEngine::Transform transform)
{
    return std::string();
}

#pragma endregion
