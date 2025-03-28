#pragma once
#include "CondorEngine/pch.h"
// internal
#include "CondorEngine/object.h"

namespace CondorEngine
{
	class SceneObject;
	class Collider;
	struct Collision;

	/// @brief Base engine scene object component class.
	class DllExport Component : public Object
	{
		friend SceneObject;

	public:
		/// @brief Class constructor.
		Component();

	public:
		/// @brief Update this component.
		void HierarchyUpdate();
		/// @brief Fixed update this component.
		void HierarchyFixedUpdate();
		/// @brief Late update this component.
		void HierarchyLateUpdate();
		/// @brief OnCollision event.
		/// @param other Collision data.
		virtual void OnCollision(Collision collision);

	private:
		/// @brief Check for first update call on this Component. If false, Start should be called first.
		bool hasDoneFirstUpdate = false;
		/// @brief The SceneObject this Component is on.
		SceneObject *sceneObject;

	public:
		/// @brief Get this Component's SceneObject.
		/// @return SceneObject.
		SceneObject *getSceneObject();
	};
}
