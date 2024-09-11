#pragma once

// third party
#include "glm/ext.hpp"
// std
#include <iostream>
#include <vector>
#include <string>
using std::vector;


namespace CondorEngine {

#pragma region Numeric Types

	/// <summary> RGBA values for color. (Abstract of glm::vec4) </summary>
	typedef glm::vec4 Color;
	/// <summary> RGB values for color. (Abstract of glm::vec3) </summary>
	typedef glm::vec3 ColorRGB;
	/// <summary> 2 dimensional vector. (Abstract of glm::vec2) </summary>
	typedef glm::vec2 Vector2;
	/// <summary> 3 dimensional vector. (Abstract of glm::vec3) </summary>
	typedef glm::vec3 Vector3;
	/// <summary> 4 dimensional vector. (Abstract of glm::vec4) </summary>
	typedef glm::vec4 Vector4;
	/// <summary> Rotational information. (Abstract of glm::vec4) </summary>
	typedef glm::vec4 Quaternion;
	/// <summary> Transformation matrix 4x4. (Abstract of glm::mat4) </summary>
	typedef glm::mat4 Transform;

#pragma endregion

	struct Light;
	class SceneObject;
	class Component;

#pragma region Base Classes

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

	/// <summary> Base engine scene class. </summary>
	class Scene : public Object {
	public:
		Scene();
		~Scene();
		void InternalUpdate();
		void InternalLateUpdate();
	private:
		bool hasDoneFirstUpdate = false;
		/// <summary> Scene objects marked for deletion during Scene::LateUpdate(). </summary>
		vector<SceneObject*> markedDelete;
	public:
		/// <summary> Root scene objects in the scene. </summary>
		vector<SceneObject*> hierarchy;
	public:
		/// <summary> Scene ambient light. </summary>
		ColorRGB ambientLight = ColorRGB{ .1,.1,.1 };
		/// <summary> *Temporary* Scene light. </summary>
		Light* light;
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
	/// <summary> Base engine scene object class. </summary>
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
		Transform transform;
	private:
		vector<Component*> components;
		vector<SceneObject*> children;
	public:
		Scene* getScene();
		void setScene(Scene* scene);
		Transform getTransform();
		void setTransform(Transform transform);
		template <typename T> T* AddComponent(T* component) {
			components.push_back(component);
			component->setSceneObject(this);
			return component;
		}
		Component* AddComponent(Component* component) {
			return AddComponent<Component>(component);
		}
	};

	/// <summary> Base engine scene object component class. </summary>
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

#pragma endregion
}
