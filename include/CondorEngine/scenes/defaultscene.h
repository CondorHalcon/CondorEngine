#pragma once
#include "CondorEngine/pch.h"
// internal
#include "CondorEngine/scene.h"

namespace CondorEngine
{
	/// @brief Default scene for the engine. Has a floor and a spectator camera.
	class DllExport DefaultScene : public Scene
	{
	public:
		/// @brief Default scene constructor.
		DefaultScene();
		/// @brief Default scene destructor.
		~DefaultScene();
	};
}
