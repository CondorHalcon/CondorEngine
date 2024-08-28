#pragma once
#include "renderer.h"

static class Primitive
{
public:
	static Shader LoadBasicShader();
	static Shader LoadDiffuseShader();
	static Shader LoadUVShader();
	static Shader LoadNormalShader(bool isObjectSpace = false);
	static Geometry MakeSimpleCube();
	static Geometry MakeCube();
};

