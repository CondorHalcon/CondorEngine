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
		template <typename T> T* Instanciate(T* sceneObject) {
			sceneObject->setScene(this);
			this->hiearchy.push_back(sceneObject);
			return sceneObject;
		}
		SceneObject* Instanciate(SceneObject* sceneObject) {
			return Instanciate<SceneObject>(sceneObject);
		}
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
	protected:
		SceneObject* parent;
		mat4 transform;
	private:
		vector<Component*> components;
		vector<SceneObject*> children;
	public:
		Scene* getScene();
		void setScene(Scene* scene);
		mat4 getTransform();
		void setTransform(mat4 transfrom);
		template <typename T> T* AddComponent(T* component) {
			components.push_back(component);
			component->setSceneObject(this);
			return component;
		}
		Component* AddComponent(Component* component) {
			return AddComponent<Component>(component);
		}
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
