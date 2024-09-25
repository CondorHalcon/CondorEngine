#pragma once
#include "../application.h"
#include "../core.h"
#include "../renderer.h"
#include "camera.h"
#include "../debug.h"
#include "light.h"

// third party
#include "glew/glew.h"
#include "glm/glm.hpp"


namespace CondorEngine {
#pragma region Material

	/// @brief Mesh material class.
	class Material : public Object {
	public:
		/// @brief Class constructor.
		/// @param shader Material shader.
		Material(Shader* shader);
		/// @brief Class deconstructor.
		~Material();
		/// @brief Update material.
		void Update() override;
	protected:
		/// @brief Material Shader reference.
		Shader* shader;
		/// @brief Model transform matrix.
		Transform transform;
	public:
		/// @brief Set material shader.
		/// @param shader Shader to set.
		void setShader(Shader* shader);
		/// @brief Get material Shader.
		/// @return Material Shader.
		Shader* getShader();
		/// @brief Set model transform matrix.
		/// @param transform Model transform matrix.
		void setTransform(Transform transform);
	protected:
		/// @brief Get the location of a uniform.
		/// @param name Name of the uniform.
		/// @return Uniform location.
		int GetUniformLocation(const char* name);
		/// @brief Set shader uniforms for `Transform`.
		/// @param location Shader layout location.
		/// @param value Uniform value.
		void SetUniform(GLuint location, const Transform& value); // for transforms
		/// @brief Set shader uniforms for `Texture`.
		/// @param location Shader layout location.
		/// @param value Uniform value.
		/// @param textureSlot
		void SetUniform(GLuint location, const Texture& value, int textureSlot); // for textures
		/// @brief Set Shader uniforms for `Vector3` and `ColorRGB`.
		/// @param location Shader layout location.
		/// @param value Uniform value.
		void SetUniform(GLuint location, const glm::vec3& value); // for rgb color & positions
		/// @brief Set shader uniform for `Vector4` and `Color`.
		/// @param location Shader layout location.
		/// @param value Uniform value.
		void SetUniform(GLuint location, const glm::vec4& value); // for color and quaternions
		/// @brief Set Shader uniforms for `Vector3` and `ColorRGB` arrays.
		/// @param location Shader layout location.
		/// @param count Length of array
		/// @param values Uniform value.
		void SetUniform(GLuint location, int count, const glm::vec3 &values);
	};

#pragma endregion 

#pragma region Mesh

	/// @brief Mesh component class.
	class Mesh : public Component {
	public:
		/// @brief Class constructor.
		/// @param verts Mesh vertices.
		/// @param vertCount Mesh vertex count.
		/// @param indices Mesh indices.
		/// @param indexCount Mesh index count.
		Mesh(const Vertex* const verts, GLsizei vertCount, const GLuint* indices, GLsizei indexCount);
		/// @brief Class constructor.
		/// @param verts Mesh vertices.
		/// @param indices Mesh indices.
		Mesh(const std::vector<Vertex> verts, const std::vector<GLuint> indices);
		/// @brief Load a mesh from and `.obj` file.
		/// @param filename Mesh file path.
		/// @param material Material to assign to the mesh.
		/// @return Loaded mesh.
		static Mesh* LoadMeshFromFile(const char* filename, Material* material);
		/// @brief Load a mesh from and `.obj` file.
		/// @param filename Mesh file path.
		/// @return Loaded mesh.
		static Mesh* LoadMeshFromFile(const char* filename);
		/// @brief Class deconstructor.
		~Mesh();
	private:
		/// @brief vertex array object
		GLuint vao;
		/// @brief vertex buffer object
		GLuint vbo;
		/// @brief index buffer object
		GLuint ibo;
		/// @brief index count
		GLuint size;
	public:
		/// @brief Render shader for the mesh.
		Material* material;
		/// @brief Update and render mesh.
		void Update() override;
	};

#pragma endregion

#pragma region Preset Materials
	/// @brief Unlit material.
	class M_Unlit : public Material {
	public:
		/// @brief Class constructor.
		M_Unlit() : Material(Shader::LoadShader("shaders/basic.vert", "shaders/basic.frag")) {
			sampleTex = nullptr;
		}
		/// @brief Update shader uniforms.
		void Update() override {
			Material::Update();
			if (sampleTex != nullptr) {
				SetUniform(3, *sampleTex, 0);
			}
		}
		/// @brief Albedo texture.
		CondorEngine::Texture* sampleTex;
	};
	/// @brief Simple lit material.
	class M_Lit : public Material {
	protected:
		/// @brief Class constructor
		/// @param shader Shader this material will use.
		M_Lit(Shader* shader) : Material(shader) {
			sampleTex = nullptr;
		}
	public:
		/// @brief Class constructor.
		M_Lit() : M_Lit(Shader::LoadShader("shaders/directional.vert", "shaders/phong.frag")) { }
		/// @brief Update shader uniforms.
		void Update() override {
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
		/// @brief Albedo texture.
		Texture* sampleTex;
	};
	class M_ComplexLit : public M_Lit {
	public:
		static const int MAX_LIGHTS = 2;
		/// @brief Class constructor.
		M_ComplexLit() : M_Lit(Shader::LoadShader("shaders/directional.vert", "shaders/phong_multi-light.frag")) {
			Debug::Log("M_ComplexLit()");
		}
		void Update() override {
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
	};
	/// @brief UV material.
	class M_UV : public Material {
	public:
		/// @brief Class constructor.
		M_UV() : Material(Shader::LoadShader("shaders/basic.vert", "shaders/uv.frag")) {}
	};
	/// @brief Object normal material.
	class M_Normal : public Material {
	public:
		/// @brief Class constructor.
		M_Normal() : Material(Shader::LoadShader("shaders/basic.vert", "shaders/normal.frag")) {}
	};
	/// @brief Screen space normal material.
	class M_ScreenNormal : public Material {
	public:
		/// @brief Class constructor.
		M_ScreenNormal() : Material(Shader::LoadShader("shaders/directional.vert", "shaders/normal.frag")) {}
	};
#pragma endregion

}

