#pragma once
// internal
#include "math.h"
#include "object.h"
#include "sceneobject.h"
// std
#include <vector>

namespace CondorEngine {
	struct DirectionalLight;
	class Light;

    /// @brief Base engine scene class.
	class Scene : public Object {
		friend SceneObject;
	public:
		/// @brief Class constructor.
		Scene();
		/// @brief Class deconstructor.
		~Scene();
		/// @brief Update this Scene and its hierarchy.
		void HierarchyUpdate();
		/// @brief Fixed update this scene and its hierarchy.
		void HierarchyFixedUpdate();
		/// @brief Late update this Scene and its hierarchy.
		void HierarchyLateUpdate();
	private:
		/// @brief Check for first update call on the Scene. If false, Start should be called first.
		bool hasDoneFirstUpdate = false;
		/// @brief Scene objects marked for deletion during before `Scene::LateUpdate()`.
		std::vector<SceneObject*> markedDelete;
	protected:
		/// @brief Root SceneObjects in this Scene.
		std::vector<SceneObject*> hierarchy;
	public:
		/// @brief Scene ambient light.
		ColorRGB ambientLight = ColorRGB{ .1,.1,.1 };
		/// @brief *Temporary* Scene directional light.
		DirectionalLight* light;
		std::vector<Light*> sceneLights;
	public:
		/// @brief Instantiate a SceneObject into this Scene.
		/// @tparam T SceneObject type; must inherit from `CondorEngine::SceneObject`.
		/// @param sceneObject The SceneObject to instantiate.
		/// @return The instantiated SceneObject.
		template <typename T> T* Instantiate(T* sceneObject) {
			sceneObject->scene = this;
			this->hierarchy.push_back(sceneObject);
			return sceneObject;
		}
		template <typename T> T* Instantiate(T* sceneObject, Vector3 position) {
			T* so = Instantiate(sceneObject);
			so->Move(position);
			return so;
		}
		/// @brief Instantiate a SceneObject into this scene.
		/// @param sceneObject The SceneObject to instantiate.
		/// @return The instantiated SceneObject.
		SceneObject* Instantiate(SceneObject* sceneObject) {
			return Instantiate<SceneObject>(sceneObject);
		}
		SceneObject* Destroy(SceneObject *sceneObject) {
			
		}
	private:
		/// @brief Remove a SceneObject from this Scene's hierarchy.
		/// @param sceneObject The SceneObject to remove.
		/// @return The removed SceneObject.
		SceneObject* RemoveSceneObject(SceneObject* sceneObject) {
			for (int i = 0; i < hierarchy.size(); i++) {
				if (hierarchy[i] == sceneObject) {
					hierarchy.erase(std::next(hierarchy.begin(), i));
				}
			}
			return sceneObject;
		}
	};
}
