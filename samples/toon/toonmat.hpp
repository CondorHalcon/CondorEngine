#pragma once
#include <CondorEngine.hpp>

using namespace CondorEngine;

class ToonMat : public Phong
{
public:
    ToonMat() : Phong() {} //Material(ResourceManager::LoadShader("CondorEngine/shaders/directional.vert", "CondorEngine/shaders/phong.frag")) {}
};