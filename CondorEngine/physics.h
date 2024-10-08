#pragma once
#include "core.h"
#include "math.h"
#include "components/rigidbody.h"

namespace CondorEngine
{
    class PhysicsScene
    {
    public:
        PhysicsScene();
        ~PhysicsScene();

        std::vector<SceneObject> sceneObjects;
        void AddSceneObject(SceneObject*);
        void RemoveSceneObject(SceneObject*);
    };
}
