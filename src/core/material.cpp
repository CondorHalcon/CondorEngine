#include "CondorEngine/material.h"
// internal
#include "CondorEngine/application.h"
#include "CondorEngine/components/camera.h"
#include "CondorEngine/components/light.h"

CondorEngine::Material::Material(Shader shader)
{
    this->name = "CondorEngine::Material";
    this->shader = shader;
    this->transform = glm::identity<Transform>();
}

void CondorEngine::Material::Update()
{
    if (Camera::Main() != nullptr)
    {
        SetUniform(0, CondorEngine::Camera::Main()->getProjectionMatrix());
        SetUniform(1, CondorEngine::Camera::Main()->getViewMatrix());
    }
    else
    {
        SetUniform(0, glm::perspective(glm::radians(60.0f), 640 / (float)480, .01f, 10.0f));
        SetUniform(1, glm::lookAt(
                          Vector3{0, 0, 0}, // camera position
                          Vector3{0, 0, 1}, // look at postion
                          Vector3{0, 1, 0}) // up vector
        );
    }
    SetUniform(2, transform);
}

void CondorEngine::Material::setShader(Shader shader)
{
    this->shader = shader;
}

CondorEngine::Shader CondorEngine::Material::getShader()
{
    return this->shader;
}

void CondorEngine::Material::setTransform(Transform transform)
{
    this->transform = transform;
}

int CondorEngine::Material::GetUniformLocation(const char *name)
{
    return glGetUniformLocation(shader.program, name);
}

void CondorEngine::Material::SetUniform(GLuint location, const Transform &value)
{
    glProgramUniformMatrix4fv(shader.program, location, 1, GL_FALSE, glm::value_ptr(value));
}

void CondorEngine::Material::SetUniform(GLuint location, const Texture &value, int textureSlot)
{
    glActiveTexture(GL_TEXTURE0 + textureSlot);
    glBindTexture(GL_TEXTURE_2D, value.handle);
    glProgramUniform1i(shader.program, location, textureSlot);
}

void CondorEngine::Material::SetUniform(GLuint location, const glm::vec3 &value)
{
    glProgramUniform3fv(shader.program, location, 1, glm::value_ptr(value));
}

void CondorEngine::Material::SetUniform(GLuint location, const glm::vec4 &value)
{
    glProgramUniform4fv(shader.program, location, 1, glm::value_ptr(value));
}

void CondorEngine::Material::SetUniform(GLuint location, int count, const glm::vec3 &values)
{
    glProgramUniform3fv(shader.program, location, (GLsizei)count, glm::value_ptr(values));
}
