#include "CondorEngine/material.h"
// internal
#include "CondorEngine/application.h"
#include "CondorEngine/components/camera.h"
#include "CondorEngine/components/light.h"

CondorEngine::Material::Material(std::string name) : Material(name, nullptr) {}

CondorEngine::Material::Material(Resource<Shader>* shader) : Material("Material", shader) {}

CondorEngine::Material::Material(std::string name, Resource<Shader>* shader) : Object(name) {
    this->shader = shader;
    this->transform = glm::identity<Transform>();
}

void CondorEngine::Material::UpdateMat(Camera* cam)
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
    if (cam != nullptr)
    {
        cameraProjection = cam->getProjectionMatrix();
        cameraView = cam->getViewMatrix();
        sunProjection = cam->getSunProjectionMatrix();
        sunView = cam->getSunViewMatrix();
    }
    SetUniform(0, cameraProjection);
    SetUniform(1, cameraView);
    SetUniform(2, transform);
    SetUniform(3, sunProjection * sunView);
}

void CondorEngine::Material::setShader(Resource<Shader>* shader)
{
    this->shader = shader;
}

CondorEngine::Resource<CondorEngine::Shader>* CondorEngine::Material::getShader()
{
    return this->shader;
}

void CondorEngine::Material::setTransform(Transform transform)
{
    this->transform = transform;
}

unsigned int CondorEngine::Material::GetUniformLocation(const char* name)
{
    return glGetUniformLocation(shader->getData().program, name);
}

void CondorEngine::Material::SetUniform(GLuint location, const float& value) {
    glProgramUniform1f(shader->getData().program, location, value);
}

void CondorEngine::Material::SetUniform(std::string name, const float& value) {
    SetUniform(GetUniformLocation(name.c_str()), value);
}

void CondorEngine::Material::SetUniform(GLuint location, const Transform& value)
{
    glProgramUniformMatrix4fv(shader->getData().program, location, 1, GL_FALSE, glm::value_ptr(value));
}

void CondorEngine::Material::SetUniform(std::string name, const Transform& value) {
    SetUniform(GetUniformLocation(name.c_str()), value);
}
void CondorEngine::Material::SetUniform(GLuint location, const Texture &value, int textureSlot)
{
    glActiveTexture(GL_TEXTURE0 + textureSlot);
    glBindTexture(GL_TEXTURE_2D, value.handle);
    glProgramUniform1i(shader->getData().program, location, textureSlot);
}

void CondorEngine::Material::SetUniform(std::string name, const Texture& value, int textureSlot) {
    SetUniform(GetUniformLocation(name.c_str()), value, textureSlot);
}

void CondorEngine::Material::SetUniform(GLuint location, const glm::vec3 &value)
{
    glProgramUniform3fv(shader->getData().program, location, 1, glm::value_ptr(value));
}

void CondorEngine::Material::SetUniform(std::string name, const glm::vec3& value) {
    SetUniform(GetUniformLocation(name.c_str()), value);
}

void CondorEngine::Material::SetUniform(GLuint location, const glm::vec4 &value)
{
    glProgramUniform4fv(shader->getData().program, location, 1, glm::value_ptr(value));
}

void CondorEngine::Material::SetUniform(std::string name, const glm::vec4& value) {
    SetUniform(GetUniformLocation(name.c_str()), value);
}

void CondorEngine::Material::SetUniform(GLuint location, int count, const glm::vec3 &values)
{
    glProgramUniform3fv(shader->getData().program, location, (GLsizei)count, glm::value_ptr(values));
}

void CondorEngine::Material::SetUniform(std::string name, int count, const glm::vec3& values) {
    SetUniform(GetUniformLocation(name.c_str()), count, values);
}
