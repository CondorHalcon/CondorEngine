#include "primitive.h"
// third party
#include "glew/glew.h"
#include "glm/glm.hpp"

CondorEngine::Primitive::Primitive(PrimitiveType type, Material* material)
{
    this->name = "CondorEngine::Primitive";
    switch (type)
    {
    case CondorEngine::SimpleCube:
        mesh = MakeSimpleCube();
        break;
    case CondorEngine::Cube:
        mesh = MakeCube();
        break;
    case CondorEngine::Plane:
        mesh = MakePlane();
        break;
    case CondorEngine::Sphere:
        mesh = MakeSphere();
        break;
    default:
        mesh = nullptr;
        break;
    }
    AddComponent(mesh);
    mesh->material = material;
}

CondorEngine::Primitive::Primitive(PrimitiveType type) : 
    CondorEngine::Primitive::Primitive(type, new M_Lit()) { }

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

CondorEngine::Mesh* CondorEngine::Primitive::MakeSphere() 
{
    std::vector<Vertex> verts;

    float radius = 0.5f;
    int longCount = 32;
    int latCount = 16;

    float x, y, z; // vertex position
    float xy; // vertex plane position
    float nx, ny, nz; // vertex normal

    float lengthInv = 1.0f / radius; // length inversion
    float s, t; // vertex texCoordinates

    float longStep = 2 * Math::PI / (float)longCount; // max distance between longitude
    float latStep = Math::PI / (float)latCount; // distance between latitude
    float longAngle, latAngle; // lat and long angle along a plane intersection

    Vertex v;
    v.col = {1, 1, 1, 1}; // set default color

    for (int i = 0; i <= latCount; i++) 
    {
        latAngle = Math::PI / 20.f - (float)i * latStep; // starting from 0 to 2pi
        xy = radius * cosf(latAngle); // r * cos(u)
        z = radius * sinf(latAngle); // r * sin(u)

        // increment for n of vertices per loop
        // first and last vertices have same position and normal, but different tex coords
        for (int j = 0; j <= longCount; j++)
        {
            //begins at zero
            longAngle = j * longStep; // starting from 0 to 2pi

            // vertex position (x, y, z)
            x = xy * cosf(longAngle); // r * cos(u) * cos(v)
            y = xy * sinf(longAngle); // r * cos(u) * sin(v)

            v.pos = Vector4(x, y, z, 1);

            // normalize vertex normal (nx, ny, nz)
            nx = x * lengthInv;
            ny = y * lengthInv;
            nz = z * lengthInv;

            v.normal = Vector3(nx, ny, nz);

            // vertex tex coord  (s, t) range between [0, 1]
            s = (float)j / longCount;
            t = (float)i / latCount;

            v.uv = Vector2(s, t);
            verts.push_back(v);
        }
    }

    // set order of vertices for triangulation
    std::vector<GLuint> indices;

    int k1, k2; // index count shorthand
    for (int i = 0; i < latCount; i++)
    {
        k1 = i * (longCount + 1); // beginning of current stack
        k2 = k1 + longCount + 1; // beginning of next stack

        for (int j = 0; j < longCount; j++, k1++, k2++)
        {
            // 2 triangles for each face excluding first and last loops
            // k1 => k2 => k1+1
            if (i != 0) {
                indices.push_back(k1);
                indices.push_back(k2);
                indices.push_back(k1 + 1);
            }
            // k1+1 => k2 => k2+1
            if (i !=(latCount - 1)) {
                indices.push_back(k1 + 1);
                indices.push_back(k2);
                indices.push_back(k2 + 1);
            }
        }
    }

    // TODO fix sphere
    return new Mesh(verts, indices);
}

CondorEngine::Mesh* CondorEngine::Primitive::MakeCylinder()
{
    int sides = 32;
    float height = 1.0f;
    float radius = .5f;
    float sectorStep = 2 * Math::PI / (float)sides;
    float sectorAngle; // for radian

    std::vector<Vector3> unitCircleVertices;
    for (int i = 0; i <= sides; i++)
    {
        sectorAngle = i * sectorStep;
        unitCircleVertices.push_back(Vector3(cos(sectorAngle), sin(sectorAngle), 0.0f)); // xyz
    }

    std::vector<Vertex> verts;
    // TODO complete
    return nullptr;
}

CondorEngine::Mesh* CondorEngine::Primitive::MakePlane()
{
    std::vector<Vertex> verts = {
        { // 0: vertex
            Vector4{.5f, 0, .5f, 1}, // position
            Vector4{1, 1, 1, 1}, // vertex color
            Vector2{0.0f, 0.0f}, // vertex uv
            Vector3{0, 1, 0}  // vertex normal
        },
        { // 1: vertex
            Vector4{-.5f, 0, .5f, 1}, // position
            Vector4{1, 1, 1, 1}, // vertex color
            Vector2{1.0f, 0.0f}, // vertex uv
            Vector3{0, 1, 0}  // vertex normal
        },
        { // 2: vertex
            Vector4{.5f, 0, -.5f, 1}, // position
            Vector4{1, 1, 1, 1}, // vertex color
            Vector2{0.0f, 1.0f}, // vertex uv
            Vector3{0, 1, 0}  // vertex normal
        },
        { // 3: vertex
            Vector4{-.5f, 0, -.5f, 1}, // position
            Vector4{1, 1, 1, 1}, // vertex color
            Vector2{1.0f, 1.0f}, // vertex uv
            Vector3{0, 1, 0}  // vertex normal
        },
    };
    std::vector<GLuint> indicies = {
        0, 2, 1,  2, 3, 1,
    };
    return new Mesh(verts, indicies);
}
