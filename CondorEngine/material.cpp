#include "material.h"
// internal
#include "application.h"
#include "components/camera.h"
#include "components/light.h"

CondorEngine::Material::Material(Shader* shader)
{
	this->name = "CondorEngine::Material";
	this->shader = shader;
	this->transform = glm::identity<Transform>();
}

CondorEngine::Material::~Material()
{
	delete shader;
}

void CondorEngine::Material::Update()
{
	if (Camera::Main() != nullptr) {
		SetUniform(0, CondorEngine::Camera::Main()->getProjectionMatrix());
		SetUniform(1, CondorEngine::Camera::Main()->getViewMatrix());
	} else {
		SetUniform(0, glm::perspective(glm::radians(60.0f), 640 / (float)480, .01f, 10.0f));
		SetUniform(1, glm::lookAt(
		Vector3{ 0,0,0 }, // camera position
		Vector3{ 0,0,1 }, // look at postion
		Vector3{ 0,1,0 }) // up vector
		);
	}
	SetUniform(2, transform);
}

void CondorEngine::Material::setShader(Shader* shader)
{
	delete shader;
	this->shader = shader;
}

CondorEngine::Shader* CondorEngine::Material::getShader()
{
	return this->shader;
}

void CondorEngine::Material::setTransform(Transform transform)
{
	this->transform = transform;
}

int CondorEngine::Material::GetUniformLocation(const char *name)
{
	return glGetUniformLocation(shader->program, name);
}

void CondorEngine::Material::SetUniform(GLuint location, const Transform &value)
{
	glProgramUniformMatrix4fv(shader->program, location, 1, GL_FALSE, glm::value_ptr(value));
}

void CondorEngine::Material::SetUniform(GLuint location, const Texture& value, int textureSlot)
{
	glActiveTexture(GL_TEXTURE0 + textureSlot);
	glBindTexture(GL_TEXTURE_2D, value.handle);
	glProgramUniform1i(shader->program, location, textureSlot);
}

void CondorEngine::Material::SetUniform(GLuint location, const glm::vec3& value)
{
	glProgramUniform3fv(shader->program, location, 1, glm::value_ptr(value));
}

void CondorEngine::Material::SetUniform(GLuint location, const glm::vec4& value)
{
	glProgramUniform4fv(shader->program, location, 1, glm::value_ptr(value));
}

void CondorEngine::Material::SetUniform(GLuint location, int count, const glm::vec3 &values)
{
	glProgramUniform3fv(shader->program, location, (GLsizei)count, glm::value_ptr(values));
}

#pragma region Preset Materials

CondorEngine::M_Unlit::M_Unlit() : CondorEngine::Material(Shader::LoadShader("shaders/basic.vert", "shaders/basic.frag")) 
{
	sampleTex = nullptr;
}

void CondorEngine::M_Unlit::Update()
{
    Material::Update();
    if (sampleTex != nullptr) {
        SetUniform(3, *sampleTex, 0);
    }
}

CondorEngine::M_Lit::M_Lit(Shader* shader) : CondorEngine::Material(shader) 
{
    sampleTex = nullptr;
}

CondorEngine::M_Lit::M_Lit() : CondorEngine::M_Lit(Shader::LoadShader("shaders/directional.vert", "shaders/phong.frag")) { }

void CondorEngine::M_Lit::Update()
{
    Material::Update();
    // lighting
    if (Application::activeScene != nullptr) {
        SetUniform(3, Application::activeScene->ambientLight);
        SetUniform(4, Application::activeScene->light->color);
        SetUniform(5, Application::activeScene->light->direction);
    } else {
        SetUniform(3, ColorRGB{ .5f, .5f, .5f });
        SetUniform(4, ColorRGB{ .5f, .5f, .5f });
        SetUniform(5, Vector3{ .3f, .3f, .3f });
    }
    // camera position
    if (Camera::Main() != nullptr) {
        SetUniform(6, Camera::Main()->getPosition());
    } else {
        SetUniform(6, Vector3{ 0,0,0 });
    }
    // texture
    if (sampleTex != nullptr) {
        SetUniform(7, *sampleTex, 0);
    }
}

CondorEngine::M_ComplexLit::M_ComplexLit() : CondorEngine::M_Lit(Shader::LoadShader("shaders/directional.vert", "shaders/phong_multi-light.frag")) {}

void CondorEngine::M_ComplexLit::Update() 
{
    Material::Update();
    // lighting
    ColorRGB lightColors[MAX_LIGHTS];
    Vector3 lightDirections[MAX_LIGHTS];
    if (Application::activeScene != nullptr) {
        lightColors[0] = Application::activeScene->light->color;
        lightDirections[0] = Application::activeScene->light->direction;
        for (int i = 0; i < MAX_LIGHTS - 1; i++) {
            if (i < Application::activeScene->sceneLights.size()) {
                lightColors[i+1] = Application::activeScene->sceneLights[i]->getLightColor();
                lightDirections[i+1] = Application::activeScene->sceneLights[i]->getLightDirection();
            } else {
            lightColors[i+1] = ColorRGB{0, 0, 0};
            lightDirections[i+1] = Vector3{1, 0, 0};
            }
        }
    } else {
        for (int i = 0; i < MAX_LIGHTS; i++) {
            lightColors[i] = ColorRGB{.04, .04, 0};
            lightDirections[i] = Vector3{1, 0, 0};
        }
    }
    SetUniform(GetUniformLocation("lightColor"), MAX_LIGHTS, *lightColors);
    SetUniform(GetUniformLocation("lightDirection"), MAX_LIGHTS, *lightDirections);
    // camera position
    if (Camera::Main() != nullptr) {
        SetUniform(4, Camera::Main()->getPosition());
    } else {
        SetUniform(4, Vector3{ 0,0,0 });
    }
    // texture
    if (sampleTex != nullptr) {
        SetUniform(5, *sampleTex, 0);
    }
}

CondorEngine::M_UV::M_UV() : CondorEngine::Material(Shader::LoadShader("shaders/basic.vert", "shaders/uv.frag")) {}

CondorEngine::M_Normal::M_Normal() : CondorEngine::Material(Shader::LoadShader("shaders/basic.vert", "shaders/normal.frag")) {}

CondorEngine::M_ScreenNormal::M_ScreenNormal() : CondorEngine::Material(Shader::LoadShader("shaders/directional.vert", "shaders/normal.frag")) {}

#pragma endregion