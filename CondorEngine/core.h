#pragma once

#include "math.h"
// third party
#include "glm/ext.hpp"
// std
#include <iostream>
#include <vector>
#include <string>
using std::vector;


namespace CondorEngine {

	struct DirectionalLight;
	class SceneObject;
	class Component;

#pragma region Object

	/// <summary> Base engine object class. </summary>
	class Object {
	public:
		Object();
		std::string name;
		bool enabled;
	public:
		/// <summary> Called before the first Update(). </summary>
		virtual void Start() {}
		/// <summary> Every tick/frame. </summary>
		virtual void Update() {}
		/// <summary> Called after the tick/frame. </summary>
		virtual void LateUpdate() {}
		virtual std::string to_string() {
			return name;
		}
	};
#pragma endregion

#pragma region Scene

	/// <summary> Base engine scene class. </summary>
	class Scene : public Object {
	public:
		Scene();
		~Scene();
		void HierarchyUpdate();
		void HierarchyLateUpdate();
	private:
		bool hasDoneFirstUpdate = false;
		/// <summary> Scene objects marked for deletion during Scene::LateUpdate(). </summary>
		vector<SceneObject*> markedDelete;
	protected:
		/// <summary> Root scene objects in the scene. </summary>
		vector<SceneObject*> hierarchy;
	public:
		/// <summary> Scene ambient light. </summary>
		ColorRGB ambientLight = ColorRGB{ .1,.1,.1 };
		/// <summary> *Temporary* Scene light. </summary>
		DirectionalLight* light;
	public:
		/// <summary> Instantiate the scene object into the active scene. </summary>
		/// <typeparam name="T"> Scene object type; must inherit from CondorEngine::SceneObject. </typeparam>
		/// <param name="sceneObject"></param>
		/// <returns> The instantiated scene object. </returns>
		template <typename T> T* Instantiate(T* sceneObject) {
			sceneObject->setScene(this);
			this->hierarchy.push_back(sceneObject);
			return sceneObject;
		}
		/// <summary> Instantiate the scene object into the active scene. </summary>
		/// <param name="sceneObject"></param>
		/// <returns></returns>
		SceneObject* Instantiate(SceneObject* sceneObject) {
			return Instantiate<SceneObject>(sceneObject);
		}
	};

#pragma endregion

#pragma region SceneObject

	/// <summary> Base engine scene object class. </summary>
	class SceneObject : public Object {
	public:
		SceneObject();
		~SceneObject();
		void HierarchyUpdate();
		void HierarchyLateUpdate();
	private:
		bool hasDoneFirstUpdate = false;
		Scene* scene;
		Vector3 position;
		Vector3 rotation;
		Vector3 scale;
	protected:
		SceneObject* parent;
		Transform transform;
	public:
		Scene* getScene();
		void setScene(Scene* scene);
		SceneObject* getParent();
		void setParent(SceneObject* newParent);
		SceneObject* getRoot();
		bool isRoot();
	public:
		Vector3 getForward();
		Vector3 getRight();
		Vector3 getUp();
		Transform getTransform();
		Transform getLocalTransform();
		Vector3 getPosition();
		Vector3 getLocalPosition();
	private:
		vector<Component*> components;
		vector<SceneObject*> children;
	public:
		template <typename T> T* AddComponent(T* component) {
			components.push_back(component);
			component->setSceneObject(this);
			return component;
		}
		Component* AddComponent(Component* component) {
			return AddComponent<Component>(component);
		}
		template <typename T> bool TryFindComponent(T& component) {
			component = nullptr;
			for (int i = 0; i < this->components.size(); i++) {
				if (typeid(this->components[i]) == typeid(T)) {
					component = this->components[i];
					return true;
				}
			}
			return false;
		}
		template <typename T> T* AddChild(T* child) {
			children.push_back(child);
			child->parent = this;
			return child;
		}
		SceneObject* AddChild(SceneObject* child) {
			return AddChild<SceneObject>(child);
		}
		void Move(Vector3 vector);
		void Rotate(Vector3 vector);
	private:
		SceneObject* RemoveChild(SceneObject* child) {
			for (int i = 0; i < children.size(); i++) {
				if (children[i] == this) {
					children.erase(std::next(children.begin(), i));
				}
			}
			return child;
		}
	};

#pragma endregion

#pragma region Component

	/// <summary> Base engine scene object component class. </summary>
	class Component : public Object {
	public:
		Component();
	public:
		void HierarchyUpdate();
		void HierarchyLateUpdate();
	private:
		bool hasDoneFirstUpdate = false;
		SceneObject* sceneObject;
	public:
		void setSceneObject(SceneObject* sceneObject);
		SceneObject* getSceneObject();
	};

#pragma endregion
}
