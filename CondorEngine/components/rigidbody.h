#pragma once
#include "../math.h"
#include "../core.h"

namespace CondorEngine
{
	class Rigidbody : public Component
	{
	public:
		/// @brief Class constructor
		Rigidbody();
		/// @brief Apply world gravity to this rigidbody.
		bool useGravity;
		/// @brief Physics update.
		void FixedUpdate() override;
		/// @brief Add force to this rigidbody.
		/// @param force Force to add.
		void AddForce(Vector3 force);
	private:
		/// @brief Current velocity.
		Vector3 velocity;
		/// @brief OnCollision event.
		void OnCollision();
	};
}
