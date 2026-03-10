#pragma once
#include "CondorEngine/pch.h"
// internal
#include "CondorEngine/math.hpp"
#include "CondorEngine/component.h"

namespace CondorEngine
{
	/// @brief Rigidbody component class.
	class DllExport Rigidbody : public Component
	{
		REFLECT_CLASS(CondorEngine::Rigidbody, Component)
		friend class Physics;

	public:
		/// @brief Class constructor
		Rigidbody();
		/// @brief Class deconstructor.
		~Rigidbody();
		/// @brief Mass of the rigidbody in kg(s).
		REFLECT_FIELD(float, mass)
		/// @brief Apply world gravity to this rigidbody.
		REFLECT_FIELD(bool, useGravity)
		/// @brief Add force to this rigidbody.
		/// @param force Force to add.
		void AddForce(Vector3 force);

	private:
		/// @brief Current velocity.
		REFLECT_FIELD(Vector3, velocity)

	public:
		/// @brief Get current rigidbody velocity.
		/// @return Vector3 velocity.
		Vector3 getVelocity();
		/// @brief Set current rigidbody velocity.
		/// @param velocity Vector3 velocity.
		void setVelocity(Vector3 velocity);
	};
}
