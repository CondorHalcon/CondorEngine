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
		/// @brief Class deconstructor.
		~Rigidbody();
		/// @brief Mass of the rigidbody in kg(s).
		float mass;
		/// @brief Apply world gravity to this rigidbody.
		bool useGravity;
		/// @brief Add force to this rigidbody.
		/// @param force Force to add.
		void AddForce(Vector3 force);
	private:
		/// @brief Current velocity.
		Vector3 velocity;
	public:
		Vector3 getVelocity();
		void setVelocity(Vector3 velocity);
	};
}
