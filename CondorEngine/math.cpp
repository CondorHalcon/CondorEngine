#include "math.h"
//std
#include <cmath>

CondorEngine::Vector3 CondorEngine::Math::TransformToPosition(Transform transform)
{
    return Vector3{transform[3], transform[7], transform[11]};
}

CondorEngine::Vector3 CondorEngine::Math::TransformToEulerRotation(Transform transform)
{
    float x = 0;
    float y = 0;
    float z = 0;
    return Vector3{ x, y, z };
}
