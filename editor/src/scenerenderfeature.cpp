#include "scenenrenderfeature.h"
#include "editor.h"
#include "editorscenecamera.hpp"

CondorEditor::SceneViewRenderFeature::SceneViewRenderFeature() {}

CondorEditor::SceneViewRenderFeature::~SceneViewRenderFeature() {
    if (instance == this) { instance = nullptr; }

    // clear buffers & textures
    Renderer::deleteFramebuffers(1, &sceneFBO);
    Renderer::deleteTextures(1, &sceneColorTex);
    Renderer::deleteRenderbuffers(1, &sceneDepthRBO);
}

void CondorEditor::SceneViewRenderFeature::CreateSceneFramebuffer(int width, int height) {
    // Cleanup old
    if (sceneFBO) {
        Renderer::deleteFramebuffers(1, &sceneFBO);
        Renderer::deleteTextures(1, &sceneColorTex);
        Renderer::deleteRenderbuffers(1, &sceneDepthRBO);
    }

    sceneSize = { width, height };

    GLuint* fbo = &sceneFBO;
    Renderer::genFramebuffers(1, &sceneFBO);
    Renderer::bindFramebuffer(GL_FRAMEBUFFER, sceneFBO);

    // Color texture
    Renderer::genTextures(1, &sceneColorTex);
    Renderer::bindTexture(GL_TEXTURE_2D, sceneColorTex);
    Renderer::texImage2D(
        GL_TEXTURE_2D, 0, GL_RGBA8,
        width, height,
        0, GL_RGBA, GL_UNSIGNED_BYTE, nullptr
    );
    Renderer::texParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    Renderer::texParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    Renderer::framebufferTexture2D(
        GL_FRAMEBUFFER,
        GL_COLOR_ATTACHMENT0,
        GL_TEXTURE_2D,
        sceneColorTex,
        0
    );

    // Depth buffer
    Renderer::genRenderbuffers(1, &sceneDepthRBO);
    Renderer::bindRenderbuffer(GL_RENDERBUFFER, sceneDepthRBO);
    Renderer::renderbufferStorage(
        GL_RENDERBUFFER,
        GL_DEPTH24_STENCIL8,
        width, height
    );

    Renderer::framebufferRenderbuffer(
        GL_FRAMEBUFFER,
        GL_DEPTH_STENCIL_ATTACHMENT,
        GL_RENDERBUFFER,
        sceneDepthRBO
    );

    if (Renderer::checkFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE) {
        // Handle error
        Debug::LogError("SceneRenderFeature :: Framebuffer incomplete!");
    }
    else {
        Debug::Log("SceneRenderFeature :: Framebuffer complete.");
    }

    Renderer::bindFramebuffer(GL_FRAMEBUFFER, 0);
}

void CondorEditor::SceneViewRenderFeature::SetBuffer() {
    Renderer::bindFramebuffer(GL_FRAMEBUFFER, sceneFBO);
    Renderer::viewport(0, 0, sceneSize.x, sceneSize.y);

    Renderer::clearColor({0.2f, 0.2f, 0.2f});
    Renderer::clear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void CondorEditor::SceneViewRenderFeature::Render() {
    SetBuffer();

    for (Mesh* mesh : Renderer::meshes) {
        // filter to only render enabled layer
        if (!mesh->getSceneObject()->layer) { continue; }

        if (mesh->material == nullptr) {
            throw("CondorEngine::Rendering::ColorRenderFeature :: Failed to render: No material set to mesh component.");
        }

        // prep shader
        mesh->material->setTransform(mesh->getSceneObject()->getTransform());
        mesh->material->UpdateMat(Editor::Instance()->sceneCamera->camera);

        // specify which shader to use
        Renderer::useProgram(mesh->material->getShader().program);
        // specify which geometry
        Renderer::bindVertexArray(mesh->data.vao);
        // draw the geometry with the shader
        Renderer::drawElements(GL_TRIANGLES, mesh->data.size, GL_UNSIGNED_INT, nullptr);
    }
}
