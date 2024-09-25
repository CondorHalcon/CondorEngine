#include "../math.h"
#include "../core.h"
#include "../components/light.h"

namespace CondorEngine {
    class SceneLight : public SceneObject {
    public:
        SceneLight();
        SceneLight(ColorRGB lightColor);
        SceneLight(ColorRGB lightColor, Vector3 lightDirection);
    public:
        Light* light;
    };
}