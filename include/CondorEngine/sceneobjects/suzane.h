#pragma once
#include "CondorEngine/pch.h"
#include "CondorEngine/sceneobject.h"
#include "CondorEngine/components/mesh.h"

namespace CondorEngine
{
    class DllExport Suzane : public SceneObject
    {
    public:
        Suzane(Material* material);
        Suzane();

        Mesh* mesh;
    };
}