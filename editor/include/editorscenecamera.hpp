#include <CondorEngine.hpp>

using namespace CondorEngine;

namespace CondorEditor
{
    class EditorSceneCamera : public SceneObject
    {
    public:
        EditorSceneCamera(std::string name = "EditorSceneCamera") : SceneObject(name) {
            camera = new Camera("EditorCamera", false);
            AddComponent(camera);
        }
        
        Camera* camera;
    };
}