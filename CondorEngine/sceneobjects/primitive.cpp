#include "primitive.h"
// third party
#include "glew/glew.h"
#include "glm/glm.hpp"

CondorEngine::Primitive::Primitive(PrimitiveType type, Material* matrial)
{
    switch (type)
    {
    case CondorEngine::SimpleCube:
        mesh = MakeSimpleCube();
        break;
    case CondorEngine::Cube:
        mesh = MakeCube();
        break;
    default:
        mesh = nullptr;
        break;
    }
    AddComponent(mesh);
    mesh->material = matrial;
}

CondorEngine::Primitive::Primitive(PrimitiveType type) : 
    CondorEngine::Primitive::Primitive(type, new M_Unlit()) { }

CondorEngine::Mesh* CondorEngine::Primitive::MakeSimpleCube()
{
    std::vector<Vertex> verts = std::vector<Vertex> {
        { // 0: vertex
            Vector4{-.5f, -.5f, .5f, 1}, // position
            Vector4{1,1,1,1}, // vertex color
            Vector2{0.0f,0.0f}, // vertex uv
            Vector3{-.7f,-.7f,.7f}  // vertex normal
        },
        { // 1: vertex
            Vector4{.5f, -.5f, .5f, 1}, // position
            Vector4{1,1,1,1}, // vertex color
            Vector2{1.0f,0.0f}, // vertex uv
            Vector3{.7f,-.7f,.7f}  // vertex normal
        },
        { // 2: vertex
            Vector4{-.5f, .5f, .5f, 1}, // position
            Vector4{1,1,1,1}, // vertex color
            Vector2{0.0f,1.0f}, // vertex uv
            Vector3{-.7f,.7f,.7f}  // vertex normal
        },
        { // 3: vertex
            Vector4{.5f, .5f, .5f, 1}, // position
            Vector4{1,1,1,1}, // vertex color
            Vector2{1.0f,1.0f}, // vertex uv
            Vector3{.7f,.7f,.7f}  // vertex normal
        },
        { // 4: vertex
            Vector4{-.5f, -.5f, -.5f, 1}, // position
            Vector4{1,1,1,1}, // vertex color
            Vector2{-1.0f,0.0f}, // vertex uv
            Vector3{-.7f,-.7f,-.7f}  // vertex normal
        },
        { // 5: vertex
            Vector4{.5f, -.5f, -.5f, 1}, // position
            Vector4{1,1,1,1}, // vertex color
            Vector2{0.0,0.0f}, // vertex uv
            Vector3{.7f,-.7f,-.7f}  // vertex normal
        },
        { // 6: vertex
            Vector4{-.5f, .5f, -.5f, 1}, // position
            Vector4{1,1,1,1}, // vertex color
            Vector2{-1.0f,1.0f}, // vertex uv
            Vector3{-.7f,.7f,-.7f}  // vertex normal
        },
        { // 7: vertex
            Vector4{.5f, .5f, -.5f, 1}, // position
            Vector4{1,1,1,1}, // vertex color
            Vector2{0.0f,1.0f}, // vertex uv
            Vector3{.7f,.7f,-.7f}  // vertex normal
        },
    };
    std::vector<GLuint> indicies = {
        0, 1, 2,  2, 1, 3,
        0, 4, 1,  1, 4, 5,
        4, 6, 5,  5, 6, 7,
        6, 2, 3,  3, 7, 6,
        0, 2, 6,  6, 4, 0,
        1, 5, 3,  3, 5, 7
    };
    return new Mesh(verts, indicies);
}

CondorEngine::Mesh* CondorEngine::Primitive::MakeCube()
{
    std::vector<Vertex> verts = std::vector<Vertex> {
        // Face: 0 (front)
        { // 0: vertex
            Vector4{-.5f, -.5f, .5f, 1}, // position
            Color{1,1,1,1}, // vertex color
            Vector2{0.0f,0.0f}, // vertex uv
            Vector3{0,0,1}  // vertex normal
        }, // A
        { // 1: vertex
            Vector4{.5f, -.5f, .5f, 1}, // position
            Color{1,1,1,1}, // vertex color
            Vector2{1.0f,0.0f}, // vertex uv
            Vector3{0,0,1}  // vertex normal
        }, // B
        { // 2: vertex
            Vector4{-.5f, .5f, .5f, 1}, // position
            Color{1,1,1,1}, // vertex color
            Vector2{0.0f,1.0f}, // vertex uv
            Vector3{0,0,1}  // vertex normal
        }, // C
        { // 3: vertex
            Vector4{.5f, .5f, .5f, 1}, // position
            Color{1,1,1,1}, // vertex color
            Vector2{1.0f,1.0f}, // vertex uv
            Vector3{0,0,1}  // vertex normal
        }, // D
        // Face: 1 (bottom)
        { // 4: vertex
            Vector4{-.5f, -.5f, -.5f, 1}, // position
            Color{1,1,1,1}, // vertex color
            Vector2{0.0f,0.0f}, // vertex uv
            Vector3{0,-1,0}  // vertex normal
        }, // E
        { // 5: vertex
            Vector4{.5f, -.5f, -.5f, 1}, // position
            Color{1,1,1,1}, // vertex color
            Vector2{1.0f,0.0f}, // vertex uv
            Vector3{0,-1,0}  // vertex normal
        }, // F
        { // 6: vertex
            Vector4{-.5f, -.5f, .5f, 1}, // position
            Color{1,1,1,1}, // vertex color
            Vector2{0.0f,1.0f}, // vertex uv
            Vector3{0,-1,0}  // vertex normal
        }, // A
        { // 7: vertex
            Vector4{.5f, -.5f, .5f, 1}, // position
            Color{1,1,1,1}, // vertex color
            Vector2{1.0f,1.0f}, // vertex uv
            Vector3{0,-1,0}  // vertex normal
        }, // B
        // Face: 2 (back)
        { // 8: vertex
            Vector4{-.5f, .5f, -.5f, 1}, // position
            Color{1,1,1,1}, // vertex color
            Vector2{1.0f,1.0f}, // vertex uv
            Vector3{0,0,-1}  // vertex normal
        }, // G
        { // 9: vertex
            Vector4{.5f, .5f, -.5f, 1}, // position
            Color{1,1,1,1}, // vertex color
            Vector2{0.0,1.0f}, // vertex uv
            Vector3{0,0,-1}  // vertex normal
        }, // H
        { // 10: vertex
            Vector4{-.5f, -.5f, -.5f, 1}, // position
            Color{1,1,1,1}, // vertex color
            Vector2{1.0f,0.0f}, // vertex uv
            Vector3{0,0,-1}  // vertex normal
        }, // E
        { // 11: vertex
            Vector4{.5f, -.5f, -.5f, 1}, // position
            Color{1,1,1,1}, // vertex color
            Vector2{0.0f,0.0f}, // vertex uv
            Vector3{0,0,-1}  // vertex normal
        }, // F
        // Face: 3 (top)
        { // 12: vertex
            Vector4{-.5f, .5f, .5f, 1}, // position
            Color{1,1,1,1}, // vertex color
            Vector2{0.0f,0.0f}, // vertex uv
            Vector3{0,1,0}  // vertex normal
        }, // C
        { // 13: vertex
            Vector4{.5f, .5f, .5f, 1}, // position
            Color{1,1,1,1}, // vertex color
            Vector2{1.0f,0.0f}, // vertex uv
            Vector3{0,1,0}  // vertex normal
        }, // D
        { // 14: vertex
            Vector4{-.5f, .5f, -.5f, 1}, // position
            Color{1,1,1,1}, // vertex color
            Vector2{0.0f,1.0f}, // vertex uv
            Vector3{0,1,0}  // vertex normal
        }, // G
        { // 15: vertex
            Vector4{.5f, .5f, -.5f, 1}, // position
            Color{1,1,1,1}, // vertex color
            Vector2{1.0f,1.0f}, // vertex uv
            Vector3{0,1,0}  // vertex normal
        }, // H
        // Face: 4 (right)
        { // 16: vertex
            Vector4{.5f, -.5f, .5f, 1}, // position
            Color{1,1,1,1}, // vertex color
            Vector2{0.0f,0.0f}, // vertex uv
            Vector3{1,0,0}  // vertex normal
        }, // B
        { // 17: vertex
            Vector4{.5f, -.5f, -.5f, 1}, // position
            Color{1,1,1,1}, // vertex color
            Vector2{1.0f,0.0f}, // vertex uv
            Vector3{1,0,0}  // vertex normal
        }, // F
        { // 18: vertex
            Vector4{.5f, .5f, .5f, 1}, // position
            Color{1,1,1,1}, // vertex color
            Vector2{0.0f,1.0f}, // vertex uv
            Vector3{1,0,0}  // vertex normal
        }, // D
        { // 19: vertex
            Vector4{.5f, .5f, -.5f, 1}, // position
            Color{1,1,1,1}, // vertex color
            Vector2{1.0f,1.0f}, // vertex uv
            Vector3{1,0,0}  // vertex normal
        }, // H
        // Face: 5 (left)
        { // 20: vertex
            Vector4{-.5f, -.5f, -.5f, 1}, // position
            Color{1,1,1,1}, // vertex color
            Vector2{0.0f,0.0f}, // vertex uv
            Vector3{-1,0,0}  // vertex normal
        }, // E
        { // 21: vertex
            Vector4{-.5f, -.5f, .5f, 1}, // position
            Color{1,1,1,1}, // vertex color
            Vector2{1.0f,0.0f}, // vertex uv
            Vector3{-1,0,0}  // vertex normal
        }, // A
        { // 22: vertex
            Vector4{-.5f, .5f, -.5f, 1}, // position
            Color{1,1,1,1}, // vertex color
            Vector2{0.0f,1.0f}, // vertex uv
            Vector3{-1,0,0}  // vertex normal
        }, // G
        { // 23: vertex
            Vector4{-.5f, .5f, .5f, 1}, // position
            Color{1,1,1,1}, // vertex color
            Vector2{1.0f,1.0f}, // vertex uv
            Vector3{-1,0,0}  // vertex normal
        }, // C
    };
    std::vector<GLuint> indicies = {
        0, 1, 2,   2, 1, 3,
        4, 5, 6,   6, 5, 7,
        8, 9, 10,  10, 9, 11,
        12, 13, 14,  14, 13, 15,
        16, 17, 18,   18, 17, 19,
        20, 21, 22,   22, 21, 23
        };
    return new Mesh(verts, indicies);
}