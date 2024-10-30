#pragma once
// internal
#include "math.h"
#include "object.h"
#include "component.h"
// std
#include <string>
#include <vector>

#ifndef SCENE_OBJECT_H
#define SCENE_OBJECT_H
namespace CondorEngine {
	class Scene;
	struct Collision;

    /// @brief Base SceneObject class.
	class SceneObject : public Object {
		friend Scene;
	public:
		/// @brief Class constructor.
		SceneObject();
		/// @brief Class deconstructor.
		~SceneObject();
		/// @brief Update this SceneObject, its components, and its children.
		void HierarchyUpdate();
		/// @brief Fixed update this SceneObject, its components, and its children.
		void HierarchyFixedUpdate();
		/// @brief Late update this SceneObject, its components, and its children.
		void HierarchyLateUpdate();
		/// @brief Call OnCollision event on this SceneObject and its components.
		/// @param collision Collision data.
		void ObjectOnCollision(Collision collision);
		/// @brief OnCollision event.
		virtual void OnCollision(Collision collision);
	private:
		/// @brief Check for first update call on the SceneObject. If false, Start should be called first.
		bool hasDoneFirstUpdate = false;
		/// @brief The Scene this SceneObject has been instantiated into.
		Scene* scene;
	protected:
		/// @brief This SceneObject's parent if it is not a root object.
		SceneObject* parent;
		/// @brief This SceneObject's local transformation matrix.
		Transform transform;
#pragma region Getters and Setters
	public:
		/// @brief Get the Scene this SceneObject has been instantiated into.
		/// @return Present Scene.
		Scene* getScene();
		/// @brief Set the Scene this SceneObject is in.
		/// @param scene The scene this SceneObject will be set to.
		void setScene(Scene* scene);
		/// @brief Get this SceneObject's parent.
		/// @return The parent.
		SceneObject* getParent();
		/// @brief Set this SceneObject's parent.
		/// @param newParent The new parent. (Set to `nullptr` to make this as a root SceneObject)
		void setParent(SceneObject* newParent);
		/// @brief Get this SceneObject's root SceneObject. Self if this SceneObject does not have a parent.
		/// @return Root SceneObject.
		SceneObject* getRoot();
		/// @brief Check if this is a root SceneObject.
		/// @return True if root, false if this SceneObject has a parent.
		bool isRoot();
		/// @brief Get number of child SceneObjects in this SceneObject.
		/// @return Number of children.
		unsigned int getChildCount();
	public:
		/// @brief Get the world relative forward direction of this SceneObject.
		/// @return Forward direction.
		Vector3 getForward();
		/// @brief Get the world relative right direction of this SceneObject.
		/// @return Right direction.
		Vector3 getRight();
		/// @brief Get the world relative up direction of this SceneObject.
		/// @return Up direction.
		Vector3 getUp();
		/// @brief Get this SceneObject's world transform matrix. (Identical to the local transform matrix if this is the root SceneObject.)
		/// @return Transform matrix.
		Transform getTransform();
		/// @brief Get this SceneObject's local transform matrix. (Identical to the world transform matrix if this is the root SceneObject.)
		/// @return Transform matrix.
		Transform getLocalTransform();
		/// @brief Get this SceneObject's world position. (Identical to the world position if this is the root SceneObject.)
		/// @return World position.
		Vector3 getPosition();
		/// @brief Set this SceneObject's world position. (Identical to the local position if this is the root SceneObject.)
		void setPosition(Vector3 position);
		/// @brief Get this SceneObject's local position. (Identical to the world position if this is the root SceneObject.)
		/// @return Local position.
		Vector3 getLocalPosition();
		/// @brief Set this SceneObject's local position. (Identical to the world position if this is the root SceneObject.)
		/// @param position Local position.
		void setLocalPosition(Vector3 position);
		/// @brief Get this SceneObject's world rotation. (Identical to the local rotation if this is the root SceneObject.)
		/// @return World rotation.
		Quaternion getRotation();
		/// @brief Get this SceneObject's local rotation. (Identical to the world rotation if this is the root SceneObject.)
		/// @return Local rotation.
		Quaternion getLocalRotation();
		/// @brief Get this SceneObject's world scale. (Identical to the local scale if this is the root SceneObject.)
		/// @return World scale.
		Vector3 getScale();
		/// @brief Get this SceneObject's local scale. (Identical to the world scale if this is the root SceneObject.)
		/// @return Local scale.
		Vector3 getLocalScale();
#pragma endregion
	private:
		/// @brief List of Components on this SceneObject.
		std::vector<Component*> components;
		/// @brief List of child SceneObjects on this SceneObject.
		std::vector<SceneObject*> children;
#pragma region Component Methods
	public:
		/// @brief Add a Component to this SceneObject.
		/// @tparam T Component type; must inherit from `CondorEngine::Component`.
		/// @param component Component to add.
		/// @return Added Component.
		template <typename T> T* AddComponent(T* component) {
			components.push_back(component);
			component->sceneObject = this;
			return component;
		}
		/// @brief Add a Component to this SceneObject.
		/// @param component Component object to add.
		/// @return Added Component object.
		Component* AddComponent(Component* component) {
			return AddComponent<Component>(component);
		}
		/// @brief Find a Component of type on this SceneObject.
		/// @tparam T Type of Component to find.
		/// @param component out Component object.
		/// @return True if it found a Component of type `T`, false if it did not.
		template <typename T> bool TryFindComponent(T** component) {
			for (int i = 0; i < this->components.size(); i++) {
				if (dynamic_cast<T*>(components[i])) {
					*component = dynamic_cast<T*>(components[i]);
					return true;
				}
			}
			*component = nullptr;
			return false;
		}
		/// @brief Find a Component of type in this SceneObject.
		/// @tparam T Type of Component to find.
		/// @return Component if found, nullptr if the Component type doesn't exist on this SceneObject.
		template <typename T> T* GetComponent() {
			T *component;
			if (TryFindComponent<T>(&component)) {
				return component;
			}
			return nullptr;
		}
		/// @brief Find a Component of type on this SceneObject or its children. `WARNING`: This is a recursive function that loops through every component on every child.
		/// @tparam T Type of Component to find.
		/// @param component out Component object.
		/// @return True if it found a Component of type `T`, false if it did not.
		template <typename T> bool TryFindComponentInChildren(T** component) {
			if (TryFindComponent<T>(component)) {
				return true;
			}
			for (int i = 0; i < this->children.size(); i++) {
				if (children[i]->TryFindComponentInChildren<T>(component)) {
					return true;
				}
			}
			*component = nullptr;
			return false;
		}
		/// @brief Find a Component of type on this SceneObject or its children. `WARNING`: This is a recursive function that loops through every component on every child.
		/// @tparam T Type of Component to find.
		/// @return Component if found, nullptr if the Component type doesn't exist on this SceneObject or it's children.
		template <typename T> T* GetComponentInChildren() {
			T *component;
			if (TryFindComponentInChildren<T>(&component)) {
				return component;
			}
			return nullptr;
		}
		/// @brief Find a Component of type on this SceneObject or its parents. `WARNING`: This is a recursive function that loops through every component on every parent.
		/// @tparam T Type of Component to find.
		/// @param component out Component object.
		/// @return True if it found a Component of type `T`, false if it did not.
		template <typename T> bool TryFindComponentInParent(T** component) {
			if (TryFindComponent<T>(component)) {
				return true;
			}
			if (parent != nullptr) {
				return parent->TryFindComponentInParent<T>(component);
			}
			*component = nullptr;
			return false;
		}
		/// @brief Find a Component of type on this SceneObject or its children. `WARNING`: This is a recursive function that loops through every component on every child.
		/// @tparam T Type of Component to find.
		/// @return Component if found, nullptr if the Component type doesn't exist on this SceneObject or it's parents.
		template <typename T> T* GetComponentInParent() {
			T *component;
			if (TryFindComponentInParent<T>(&component)) {
				return component;
			}
			return nullptr;
		}
#pragma endregion

#pragma region Child Methods
		/// @brief Add a child to this SceneObject.
		/// @tparam T Child SceneObject type; must inherit from `CondorEngine::SceneObject`.
		/// @param child Child SceneObject to add.
		/// @return Added child of type `T`.
		template <typename T> T* AddChild(T* child) {
			if (child == this) {
				throw(std::string("SceneObject::AddChild(T*) failed : Cannot add a SceneObject as its own child"));
			}
			children.push_back(child);
			child->parent = this;
			return child;
		}
		/// @brief Add a child to this SceneObject.
		/// @tparam T Child SceneObject type; must inherit from `CondorEngine::SceneObject`.
		/// @param child Child SceneObject to add.
		/// @return Added child of type `SceneObject`.
		SceneObject* AddChild(SceneObject* child) {
			return AddChild<SceneObject>(child);
		}
		/// @brief Translate this SceneObject.
		/// @param vector Translation.
		void Move(Vector3 vector, bool worldSpace = true);
		/// @brief Rotate this SceneObject.
		/// @param vector Euler rotation.
		void Rotate(Vector3 vector, bool worldSpace = true);
		/// @brief Scale this SceneObject.
		/// @param scaler Scaler.
		void Scale(Vector3 scaler);
	private:
		/// @brief Remove a child SceneObject form this SceneObject.
		/// @param child The child to remove.
		/// @return Removed child.
		SceneObject* RemoveChild(SceneObject* child) {
			for (int i = 0; i < children.size(); i++) {
				if (children[i] == child) {
					children.erase(std::next(children.begin(), i));
				}
			}
			return child;
		}
	};
#pragma endregion
}
#endif