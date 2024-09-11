#pragma once
#include "../application.h"
#include "../core.h"
#include "../renderer.h"
#include "../camera.h"

// third party
#include "glew/glew.h"
#include "glm/glm.hpp"


namespace CondorEngine {
	class Material : public Object {
	public:
		Material(Shader* shader);
		void Update() override;
	private:
		Shader* shader;
		Transform transform;
	public:
		void setShader(Shader* shader);
		Shader* getShader();
		void setTransform(Transform transform);
	protected:
		/// <summary> Set shader uniforms for transformations. </summary>
		/// <param name="location"></param>
		/// <param name="value"></param>
		void SetUniform(GLuint location, const Transform& value); // for transforms
		/// <summary> Set shader uniforms for textures. </summary>
		/// <param name="location"></param>
		/// <param name="value"></param>
		/// <param name="textureSlot"></param>
		void SetUniform(GLuint location, const Texture& value, int textureSlot); // for textures
		/// <summary> Set Shader uniforms for positions and rgb colors. </summary>
		/// <param name="location"></param>
		/// <param name="value"></param>
		void SetUniform(GLuint location, const glm::vec3& value); // for rgb color & positions
		/// <summary> Set shader uniform for colors and quaternions. </summary>
		/// <param name="location"></param>
		/// <param name="value"></param>
		void SetUniform(GLuint location, const glm::vec4& value); // for color and quaternions
	};

	class Mesh : public Component {
	public:
		Mesh(const Vertex* const verts, GLsizei vertCount, const GLuint* indices, GLsizei indexCount);
		Mesh(const std::vector<Vertex> verts, const std::vector<GLuint> indices);
		static Mesh* LoadMeshFromFile(const char* filename);
		~Mesh();
	private:
		/// <summary> vertex array object </summary>
		GLuint vao;
		/// <summary> vertex buffer object </summary>
		GLuint vbo;
		/// <summary> index buffer object </summary>
		GLuint ibo;
		/// <summary> index count </summary>
		GLuint size;
	public:
		/// <summary> Render shader for the mesh. </summary>
		Material* material;
		void Update() override;
	};

#pragma region Materials
	class M_Unlit : public Material {
	public:
		M_Unlit() : Material(Shader::LoadShader("shaders/basic.vert", "shaders/basic.frag")) {
			sampleTex = nullptr;
		}
		void Update() override {
			Material::Update();
			if (sampleTex != nullptr) {
				SetUniform(3, *sampleTex, 0);
			}
		}
		CondorEngine::Texture* sampleTex;
	};
	class M_Lit : public Material {
	public:
		M_Lit() : Material(Shader::LoadShader("shaders/directional.vert", "shaders/phong.frag")) {
			sampleTex = nullptr;
		}
		void Update() override {
			Material::Update();
			if (sampleTex != nullptr) {
				SetUniform(3, *sampleTex, 0);
			}
			SetUniform(4, Application::activeScene->ambientLight);
			SetUniform(5, Application::activeScene->light->color);
			SetUniform(6, Application::activeScene->light->direction);
			SetUniform(7, Camera::Instance()->position);
		}
		Texture* sampleTex;
	};
	class M_UV : public Material {
	public:
		M_UV() : Material(Shader::LoadShader("shaders/basic.vert", "shaders/uv.frag")) {}
		void Update() override {
			Material::Update();
		}
	};
	class M_Normal : public Material {
	public:
		M_Normal() : Material(Shader::LoadShader("shaders/basic.vert", "shaders/normal.frag")) {}
		void Update() override {
			Material::Update();
		}
	};
	class M_ScreenNormal : public Material {
	public:
		M_ScreenNormal() : Material(Shader::LoadShader("shaders/directional.vert", "shaders/normal.frag")) {}
		void Update() override {
			Material::Update();
		}
	};
#pragma endregion

}

