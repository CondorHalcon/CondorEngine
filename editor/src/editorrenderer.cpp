#include "editorrenderer.h"
#include "editormainmenubar.h"
#include <imgui.h>
#include <imgui_internal.h>
#include <backends/imgui_impl_glfw.h>
#include <backends/imgui_impl_opengl3.h>

CondorEditor::EditorRenderFeature::EditorRenderFeature() {}

void CondorEditor::EditorRenderFeature::Render() {
    static bool hasDoneFirstDraw = false;

    ImGuiRenderFeature::Render();

    ImGuiID dockspaceId = ImGui::GetID(rootDockspace);
    ImGuiViewport* viewport = ImGui::GetMainViewport();

    if (!hasDoneFirstDraw) {
        BuildDefaultDockLayout(dockspaceId, viewport);
        hasDoneFirstDraw = true;
    }
    
    // Submit dockspace
    ImGui::DockSpaceOverViewport(dockspaceId, viewport, 0);

    EditorMainMenuBar::Instance()->DrawMainMenuBar();

    for (EditorPanel* panel : Editor::Instance()->panels) {
        panel->OnGui();
    }
}

void CondorEditor::EditorRenderFeature::BuildDefaultDockLayout(ImGuiID dockspaceId, ImGuiViewport* viewport) {

    if (ImGui::DockBuilderGetNode(dockspaceId) == nullptr) {
        ImGui::DockBuilderAddNode(dockspaceId, ImGuiDockNodeFlags_DockSpace);
        ImGui::DockBuilderSetNodeSize(dockspaceId, viewport->WorkSize);

        ImGuiID dockMain = dockspaceId;
        ImGuiID dockLeft, dockRight, dockBottom;

        ImGui::DockBuilderSplitNode(dockMain, ImGuiDir_Right, 0.2f, &dockRight, &dockMain);
        ImGui::DockBuilderSplitNode(dockMain, ImGuiDir_Down, 0.25f, &dockBottom, &dockMain);
        ImGui::DockBuilderSplitNode(dockMain, ImGuiDir_Left, 0.25f, &dockLeft, &dockMain);

        ImGui::DockBuilderDockWindow("Scene", dockMain);
        ImGui::DockBuilderDockWindow("Hierarchy", dockLeft);
        ImGui::DockBuilderDockWindow("Console", dockBottom);
        ImGui::DockBuilderDockWindow("Project", dockBottom);
        ImGui::DockBuilderDockWindow("Inspector", dockRight);

        ImGui::DockBuilderFinish(dockspaceId);
    }
}

CondorEditor::SceneViewRenderFeature* CondorEditor::SceneViewRenderFeature::instance = nullptr;

CondorEditor::SceneViewRenderFeature::SceneViewRenderFeature() {
}

CondorEditor::SceneViewRenderFeature::~SceneViewRenderFeature() {
    if (instance == this) { instance = nullptr; }

    // clear buffers & textures
    glDeleteFramebuffers(1, &sceneFBO);
    glDeleteTextures(1, &sceneColorTex);
    glDeleteRenderbuffers(1, &sceneDepthRBO);
}

CondorEditor::SceneViewRenderFeature* CondorEditor::SceneViewRenderFeature::Instance() {
    if (instance == nullptr) {
        instance = new SceneViewRenderFeature();
    }
    return instance;
}

void CondorEditor::SceneViewRenderFeature::CreateSceneFramebuffer(int width, int height) {
    // Cleanup old
    if (sceneFBO) {
        glDeleteFramebuffers(1, &sceneFBO);
        glDeleteTextures(1, &sceneColorTex);
        glDeleteRenderbuffers(1, &sceneDepthRBO);
    }

    sceneSize = { width, height };

    GLuint* fbo = &sceneFBO;
    glGenFramebuffers(1, &sceneFBO);
    glBindFramebuffer(GL_FRAMEBUFFER, sceneFBO);

    // Color texture
    glGenTextures(1, &sceneColorTex);
    glBindTexture(GL_TEXTURE_2D, sceneColorTex);
    glTexImage2D(
        GL_TEXTURE_2D, 0, GL_RGBA8,
        width, height,
        0, GL_RGBA, GL_UNSIGNED_BYTE, nullptr
    );
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    glFramebufferTexture2D(
        GL_FRAMEBUFFER,
        GL_COLOR_ATTACHMENT0,
        GL_TEXTURE_2D,
        sceneColorTex,
        0
    );

    // Depth buffer
    glGenRenderbuffers(1, &sceneDepthRBO);
    glBindRenderbuffer(GL_RENDERBUFFER, sceneDepthRBO);
    glRenderbufferStorage(
        GL_RENDERBUFFER,
        GL_DEPTH24_STENCIL8,
        width, height
    );

    glFramebufferRenderbuffer(
        GL_FRAMEBUFFER,
        GL_DEPTH_STENCIL_ATTACHMENT,
        GL_RENDERBUFFER,
        sceneDepthRBO
    );

    if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE) {
        // Handle error
    }

    glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

void CondorEditor::SceneViewRenderFeature::SetBuffer() {
    glBindFramebuffer(GL_FRAMEBUFFER, sceneFBO);
    glViewport(0, 0, sceneSize.x, sceneSize.y);

    glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
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
        mesh->material->UpdateMat(Editor::Instance()->sceneCamera);

        // specify which shader to use
        glUseProgram(mesh->material->getShader().program);
        // specify which geometry
        glBindVertexArray(mesh->data.vao);
        // draw the geometry with the shader
        glDrawElements(GL_TRIANGLES, mesh->data.size, GL_UNSIGNED_INT, nullptr);
    }
}

CondorEditor::EditorRenderer::EditorRenderer() {}

void CondorEditor::EditorRenderer::init() {
    Renderer::init();

    // initialize render features
    features = std::vector<RenderFeature*>{
        //DirectionalShadowMappingRenderFeature::Instance(),
        //SceneViewRenderFeature::Instance(),
        new EditorRenderFeature() };

    // Create GL resources for the scene framebuffer now that the GL context
    /*SceneViewRenderFeature* sceneFeature = SceneViewRenderFeature::Instance();
    if (sceneFeature) {
        sceneFeature->CreateSceneFramebuffer(sceneFeature->sceneSize.x, sceneFeature->sceneSize.y);
    }*/
}
