#pragma once
// std
#include <string>

namespace CondorEngine {
    /// @brief Base engine object class.
	class Object {
	public:
        /// @brief Class constructor.
        /// @param name Assign name to the object.
        Object(std::string name);
        /// @brief Class constructor.
		Object();
		/// @brief Object name.
		std::string name;
		/// @brief Object enabled status. Used to prevent update calls on the object.
		bool enabled;
	public:
		/// @brief Called before the first Update().
		virtual void Start() {}
		/// @brief Every tick/frame.
		virtual void Update() {}
		/// @brief Physics fixed update.
		virtual void FixedUpdate() {}
		/// @brief Called after the tick/frame.
		virtual void LateUpdate() {}
		/// @brief Object to string.
		/// @return String value of the object. (default value is the name of the object.)
        virtual std::string to_string();
    };
}

