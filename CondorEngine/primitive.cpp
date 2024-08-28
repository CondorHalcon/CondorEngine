#include "primitive.h"

Shader Primitive::LoadBasicShader()
{
    return LoadShader("shaders/basic.vert", "shaders/basic.frag");
}
Shader Primitive::LoadDiffuseShader()
{
    return LoadShader("shaders/directional.vert", "shaders/phong.frag");
}

Shader Primitive::LoadUVShader()
{
    return LoadShader("shaders/basic.vert", "shaders/uv.frag");
}
Shader Primitive::LoadNormalShader(bool isObjectSpace)
{
    if (isObjectSpace) {
        return LoadShader("shaders/basic.vert", "shaders/normal.frag");
    }
    else {
        return LoadShader("shaders/directional.vert", "shaders/normal.frag");
    }
}

Geometry Primitive::MakeSimpleCube()
{
    // Mesh
    Vertex verts[] =
    {
        { // 0: vertex
            vec4{-.5f, -.5f, .5f, 1}, // position
            vec4{1,1,1,1}, // vertex color
            vec2{0.0f,0.0f}, // vertex uv
            vec3{-.7f,-.7f,.7f}  // vertex normal
        },
        { // 1: vertex
            vec4{.5f, -.5f, .5f, 1}, // position
            vec4{1,1,1,1}, // vertex color
            vec2{1.0f,0.0f}, // vertex uv
            vec3{.7f,-.7f,.7f}  // vertex normal
        },
        { // 2: vertex
            vec4{-.5f, .5f, .5f, 1}, // position
            vec4{1,1,1,1}, // vertex color
            vec2{0.0f,1.0f}, // vertex uv
            vec3{-.7f,.7f,.7f}  // vertex normal
        },
        { // 3: vertex
            vec4{.5f, .5f, .5f, 1}, // position
            vec4{1,1,1,1}, // vertex color
            vec2{1.0f,1.0f}, // vertex uv
            vec3{.7f,.7f,.7f}  // vertex normal
        },
        { // 4: vertex
            vec4{-.5f, -.5f, -.5f, 1}, // position
            vec4{1,1,1,1}, // vertex color
            vec2{-1.0f,0.0f}, // vertex uv
            vec3{-.7f,-.7f,-.7f}  // vertex normal
        },
        { // 5: vertex
            vec4{.5f, -.5f, -.5f, 1}, // position
            vec4{1,1,1,1}, // vertex color
            vec2{0.0,0.0f}, // vertex uv
            vec3{.7f,-.7f,-.7f}  // vertex normal
        },
        { // 6: vertex
            vec4{-.5f, .5f, -.5f, 1}, // position
            vec4{1,1,1,1}, // vertex color
            vec2{-1.0f,1.0f}, // vertex uv
            vec3{-.7f,.7f,-.7f}  // vertex normal
        },
        { // 7: vertex
            vec4{.5f, .5f, -.5f, 1}, // position
            vec4{1,1,1,1}, // vertex color
            vec2{0.0f,1.0f}, // vertex uv
            vec3{.7f,.7f,-.7f}  // vertex normal
        },
    };
    GLuint indicies[] = {
        0, 1, 2,  2, 1, 3,
        0, 4, 1,  1, 4, 5,
        4, 6, 5,  5, 6, 7,
        6, 2, 3,  3, 7, 6,
        0, 2, 6,  6, 4, 0,
        1, 5, 3,  3, 5, 7
    };
    return MakeGeometry(verts, 8, indicies, 36);
}

Geometry Primitive::MakeCube()
{
    Vertex verts[] =
    {
        // Face: 0 (front)
        { // 0: vertex
            vec4{-.5f, -.5f, .5f, 1}, // position
            vec4{1,1,1,1}, // vertex color
            vec2{0.0f,0.0f}, // vertex uv
            vec3{0,0,1}  // vertex normal
        }, // A
        { // 1: vertex
            vec4{.5f, -.5f, .5f, 1}, // position
            vec4{1,1,1,1}, // vertex color
            vec2{1.0f,0.0f}, // vertex uv
            vec3{0,0,1}  // vertex normal
        }, // B
        { // 2: vertex
            vec4{-.5f, .5f, .5f, 1}, // position
            vec4{1,1,1,1}, // vertex color
            vec2{0.0f,1.0f}, // vertex uv
            vec3{0,0,1}  // vertex normal
        }, // C
        { // 3: vertex
            vec4{.5f, .5f, .5f, 1}, // position
            vec4{1,1,1,1}, // vertex color
            vec2{1.0f,1.0f}, // vertex uv
            vec3{0,0,1}  // vertex normal
        }, // D
        // Face: 1 (bottom)
        { // 4: vertex
            vec4{-.5f, -.5f, -.5f, 1}, // position
            vec4{1,1,1,1}, // vertex color
            vec2{0.0f,0.0f}, // vertex uv
            vec3{0,-1,0}  // vertex normal
        }, // E
        { // 5: vertex
            vec4{.5f, -.5f, -.5f, 1}, // position
            vec4{1,1,1,1}, // vertex color
            vec2{1.0f,0.0f}, // vertex uv
            vec3{0,-1,0}  // vertex normal
        }, // F
        { // 6: vertex
            vec4{-.5f, -.5f, .5f, 1}, // position
            vec4{1,1,1,1}, // vertex color
            vec2{0.0f,1.0f}, // vertex uv
            vec3{0,-1,0}  // vertex normal
        }, // A
        { // 7: vertex
            vec4{.5f, -.5f, .5f, 1}, // position
            vec4{1,1,1,1}, // vertex color
            vec2{1.0f,1.0f}, // vertex uv
            vec3{0,-1,0}  // vertex normal
        }, // B
        // Face: 2 (back)
        { // 8: vertex
            vec4{-.5f, .5f, -.5f, 1}, // position
            vec4{1,1,1,1}, // vertex color
            vec2{1.0f,1.0f}, // vertex uv
            vec3{0,0,-1}  // vertex normal
        }, // G
        { // 9: vertex
            vec4{.5f, .5f, -.5f, 1}, // position
            vec4{1,1,1,1}, // vertex color
            vec2{0.0,1.0f}, // vertex uv
            vec3{0,0,-1}  // vertex normal
        }, // H
        { // 10: vertex
            vec4{-.5f, -.5f, -.5f, 1}, // position
            vec4{1,1,1,1}, // vertex color
            vec2{1.0f,0.0f}, // vertex uv
            vec3{0,0,-1}  // vertex normal
        }, // E
        { // 11: vertex
            vec4{.5f, -.5f, -.5f, 1}, // position
            vec4{1,1,1,1}, // vertex color
            vec2{0.0f,0.0f}, // vertex uv
            vec3{0,0,-1}  // vertex normal
        }, // F
        // Face: 3 (top)
        { // 12: vertex
            vec4{-.5f, .5f, .5f, 1}, // position
            vec4{1,1,1,1}, // vertex color
            vec2{0.0f,0.0f}, // vertex uv
            vec3{0,1,0}  // vertex normal
        }, // C
        { // 13: vertex
            vec4{.5f, .5f, .5f, 1}, // position
            vec4{1,1,1,1}, // vertex color
            vec2{1.0f,0.0f}, // vertex uv
            vec3{0,1,0}  // vertex normal
        }, // D
        { // 14: vertex
            vec4{-.5f, .5f, -.5f, 1}, // position
            vec4{1,1,1,1}, // vertex color
            vec2{0.0f,1.0f}, // vertex uv
            vec3{0,1,0}  // vertex normal
        }, // G
        { // 15: vertex
            vec4{.5f, .5f, -.5f, 1}, // position
            vec4{1,1,1,1}, // vertex color
            vec2{1.0f,1.0f}, // vertex uv
            vec3{0,1,0}  // vertex normal
        }, // H
        // Face: 4 (right)
        { // 16: vertex
            vec4{.5f, -.5f, .5f, 1}, // position
            vec4{1,1,1,1}, // vertex color
            vec2{0.0f,0.0f}, // vertex uv
            vec3{1,0,0}  // vertex normal
        }, // B
        { // 17: vertex
            vec4{.5f, -.5f, -.5f, 1}, // position
            vec4{1,1,1,1}, // vertex color
            vec2{1.0f,0.0f}, // vertex uv
            vec3{1,0,0}  // vertex normal
        }, // F
        { // 18: vertex
            vec4{.5f, .5f, .5f, 1}, // position
            vec4{1,1,1,1}, // vertex color
            vec2{0.0f,1.0f}, // vertex uv
            vec3{1,0,0}  // vertex normal
        }, // D
        { // 19: vertex
            vec4{.5f, .5f, -.5f, 1}, // position
            vec4{1,1,1,1}, // vertex color
            vec2{1.0f,1.0f}, // vertex uv
            vec3{1,0,0}  // vertex normal
        }, // H
        // Face: 5 (left)
        { // 20: vertex
            vec4{-.5f, -.5f, -.5f, 1}, // position
            vec4{1,1,1,1}, // vertex color
            vec2{0.0f,0.0f}, // vertex uv
            vec3{-1,0,0}  // vertex normal
        }, // E
        { // 21: vertex
            vec4{-.5f, -.5f, .5f, 1}, // position
            vec4{1,1,1,1}, // vertex color
            vec2{1.0f,0.0f}, // vertex uv
            vec3{-1,0,0}  // vertex normal
        }, // A
        { // 22: vertex
            vec4{-.5f, .5f, -.5f, 1}, // position
            vec4{1,1,1,1}, // vertex color
            vec2{0.0f,1.0f}, // vertex uv
            vec3{-1,0,0}  // vertex normal
        }, // G
        { // 23: vertex
            vec4{-.5f, .5f, .5f, 1}, // position
            vec4{1,1,1,1}, // vertex color
            vec2{1.0f,1.0f}, // vertex uv
            vec3{-1,0,0}  // vertex normal
        }, // C
    };
    GLuint indicies[] = {
        0, 1, 2,   2, 1, 3,
        4, 5, 6,   6, 5, 7,
        8, 9, 10,  10, 9, 11,
        12, 13, 14,  14, 13, 15,
        16, 17, 18,   18, 17, 19,
        20, 21, 22,   22, 21, 23
        };
    return MakeGeometry(verts, 24, indicies, 36);
}
