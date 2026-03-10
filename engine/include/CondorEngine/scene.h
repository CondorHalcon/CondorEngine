#pragma once
#include "CondorEngine/pch.h"
// internal
#include "CondorEngine/math.hpp"
#include "CondorEngine/object.h"
#include "CondorEngine/sceneobject.h"
#include "CondorEngine/rendering/renderer.h"
// std
#include <string>
#include <vector>

namespace CondorEngine
{
	class Light;

	/// @brief Base scene class.
	class DllExport Scene : public Object
	{
		friend SceneObject;

		REFLECT_CLASS(CondorEngine::Scene, Object)

	public:
		/// @brief Default class constructor.
		Scene();
		/// @brief Class constructor.
		Scene(std::string name);
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
		std::vector<SceneObject *> markedDelete;

	public:
		/// @brief Root SceneObjects in this Scene.
		REFLECT_FIELD(std::vector<SceneObject*>, hierarchy)
		/// @brief Scene ambient light.
		REFLECT_FIELD(ColorRGB, ambientLight)
		/// @brief *Temporary* Scene directional light.
		DirectionalLight light;
#pragma region SceneObject Methods
	public:
		/// @brief Instantiate a SceneObject into this Scene.
		/// @tparam T SceneObject type; must inherit from `CondorEngine::SceneObject`.
		/// @param sceneObject The SceneObject to instantiate.
		/// @param position World position to instantiate the SceneObject.
		/// @return The instantiated SceneObject.
		template <typename T>
		T *Instantiate(T *sceneObject, Vector3 position)
		{
			sceneObject->scene = this;
			this->hierarchy.push_back(sceneObject);
			sceneObject->setPosition(position);
			return sceneObject;
		}
		/// @brief Instantiate a SceneObject into this Scene.
		/// @tparam T SceneObject type; must inherit from `CondorEngine::SceneObject`.
		/// @param sceneObject The SceneObject to instantiate.
		/// @return The instantiated SceneObject.
		template <typename T>
		T *Instantiate(T *sceneObject)
		{
			T *so = Instantiate(sceneObject, Vector3{0, 0, 0});
			return so;
		}
		/// @brief Instantiate a SceneObject into this scene.
		/// @param sceneObject The SceneObject to instantiate.
		/// @return The instantiated SceneObject.
		SceneObject *Instantiate(SceneObject *sceneObject)
		{
			return Instantiate<SceneObject>(sceneObject);
		}
		/// @brief Mark a SceneObject for deletion during the next `Scene::LateUpdate()`.
		/// @param sceneObject SceneObject to delete.
		void Destroy(SceneObject *sceneObject)
		{
			markedDelete.push_back(sceneObject);
		}

	private:
		/// @brief Remove a SceneObject from this Scene's hierarchy.
		/// @param sceneObject The SceneObject to remove.
		/// @return The removed SceneObject.
		SceneObject *RemoveSceneObject(SceneObject *sceneObject)
		{
			for (int i = 0; i < hierarchy.size(); i++)
			{
				if (hierarchy[i] == sceneObject)
				{
					hierarchy.erase(std::next(hierarchy.begin(), i));
				}
			}
			return sceneObject;
		}
#pragma endregion
	};
}
