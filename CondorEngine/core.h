#pragma once

// third party
#include "glm/ext.hpp"
using glm::mat4;
using glm::vec3;
// std
#include <vector>
using std::vector;

struct Light;

namespace CondorEngine {
	class SceneObject;
	class Component;

	class Scene {
	public:
		Scene();
		~Scene();
	public:
		vector<SceneObject*> hiearchy;
		vector<SceneObject*> markedDelete;
		vec3 ambientLight = { .1,.1,.1 };
		Light* light;
	public:
		SceneObject* Instanciate(SceneObject* sceneObject);
	};

	class Object {
	public:
		bool enabled = true;
	public:
		/// <summary> Called before the first Update(). </summary>
		virtual void Start() {}
		/// <summary> Every tick/frame. </summary>
		virtual void Update() {}
		/// <summary> Called after the tick/frame. </summary>
		virtual void LateUpdate() {}
	};
	class SceneObject : public Object {
	public:
		SceneObject();
		~SceneObject();
		void InternalUpdate();
		void InternalLateUpdate();
	private:
		bool hasDoneFirstUpdate = false;
		Scene* scene;
	public:
		mat4 transform;
		vector<Component*> components;
		vector<SceneObject*> children;
	public:
		void setScene(Scene* scene);
		Scene* getScene();
	public:
		Component* AddComponent(Component* component);
	};

	class Component : public Object {
	public:
		Component(SceneObject* owner);
	public:
		void InternalUpdate();
		void InternalLateUpdate();
	private:
		bool hasDoneFirstUpdate = false;
		SceneObject* sceneObject;
	public:
		SceneObject* getSceneObject();
	};
}
