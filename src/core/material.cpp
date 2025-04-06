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
    Transform cameraProjection = glm::perspective(glm::radians(60.0f), 640 / (float)480, .01f, 10.0f);
    Transform cameraView = glm::lookAt(
        Vector3{ 0, 0, 0 }, // camera position
        Vector3{ 0, 0, 1 }, // look at postion
        Vector3{ 0, 1, 0 }  // up vector
    );
    Transform sunProjection = glm::ortho(-10.0f, 10.0f, -10.0f, 10.0f, 1.f, 7.5f);
    Transform sunView = glm::lookAt(
        glm::vec3(0.0, 10.0, 0.0), // light position
        glm::vec3(0.0f, -1.0, 0.0f), // look at position
        glm::vec3(0.0f, 1.0f, 0.0f) // up vector
    );
    if (Camera::Main() != nullptr)
    {
        cameraProjection = Camera::Main()->getProjectionMatrix();
        cameraView = Camera::Main()->getViewMatrix();
        sunProjection = Camera::Main()->getSunProjectionMatrix();
        sunView = Camera::Main()->getSunViewMatrix();
    }
    SetUniform(0, cameraProjection);
    SetUniform(1, cameraView);
    SetUniform(2, transform);
    SetUniform(3, sunProjection * sunView);
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

unsigned int CondorEngine::Material::GetUniformLocation(const char* name)
{
    return glGetUniformLocation(shader.program, name);
}

void CondorEngine::Material::SetUniform(GLuint location, const float& value) {
    glProgramUniform1f(shader.program, location, value);
}

void CondorEngine::Material::SetUniform(std::string name, const float& value) {
    SetUniform(GetUniformLocation(name.c_str()), value);
}

void CondorEngine::Material::SetUniform(GLuint location, const Transform& value)
{
    glProgramUniformMatrix4fv(shader.program, location, 1, GL_FALSE, glm::value_ptr(value));
}

void CondorEngine::Material::SetUniform(std::string name, const Transform& value) {
    SetUniform(GetUniformLocation(name.c_str()), value);
}
void CondorEngine::Material::SetUniform(GLuint location, const Texture &value, int textureSlot)
{
    glActiveTexture(GL_TEXTURE0 + textureSlot);
    glBindTexture(GL_TEXTURE_2D, value.handle);
    glProgramUniform1i(shader.program, location, textureSlot);
}

void CondorEngine::Material::SetUniform(std::string name, const Texture& value, int textureSlot) {
    SetUniform(GetUniformLocation(name.c_str()), value, textureSlot);
}

void CondorEngine::Material::SetUniform(GLuint location, const glm::vec3 &value)
{
    glProgramUniform3fv(shader.program, location, 1, glm::value_ptr(value));
}

void CondorEngine::Material::SetUniform(std::string name, const glm::vec3& value) {
    SetUniform(GetUniformLocation(name.c_str()), value);
}

void CondorEngine::Material::SetUniform(GLuint location, const glm::vec4 &value)
{
    glProgramUniform4fv(shader.program, location, 1, glm::value_ptr(value));
}

void CondorEngine::Material::SetUniform(std::string name, const glm::vec4& value) {
    SetUniform(GetUniformLocation(name.c_str()), value);
}

void CondorEngine::Material::SetUniform(GLuint location, int count, const glm::vec3 &values)
{
    glProgramUniform3fv(shader.program, location, (GLsizei)count, glm::value_ptr(values));
}

void CondorEngine::Material::SetUniform(std::string name, int count, const glm::vec3& values) {
    SetUniform(GetUniformLocation(name.c_str()), count, values);
}
