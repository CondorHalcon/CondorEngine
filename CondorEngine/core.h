#pragma once

// third party
#include "glm/ext.hpp"
using glm::mat4;
using glm::vec3;
// std
#include <vector>
using std::vector;


namespace CondorEngine {
	struct Light;
	class SceneObject;
	class Component;

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

	class Scene : public Object {
	public:
		Scene();
		~Scene();
		void InternalUpdate();
		void InternalLateUpdate();
	private:
		bool hasDoneFirstUpdate = false;
	public:
		vector<SceneObject*> hiearchy;
		vector<SceneObject*> markedDelete;
		vec3 ambientLight = { .1,.1,.1 };
		Light* light;
	public:
		SceneObject* Instanciate(SceneObject* sceneObject);
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
		vector<SceneObject*> children;
	private:
		vector<Component*> components;
	public:
		void setScene(Scene* scene);
		Scene* getScene();
	public:
		Component* AddComponent(Component* component);
	};

	class Component : public Object {
	public:
		Component();
	public:
		void InternalUpdate();
		void InternalLateUpdate();
	private:
		bool hasDoneFirstUpdate = false;
		SceneObject* sceneObject;
	public:
		void setSceneObject(SceneObject* sceneObject);
		SceneObject* getSceneObject();
	};
}
