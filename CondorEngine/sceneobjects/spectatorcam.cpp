#include "spectatorcam.h"

CondorEngine::SpectatorCam::SpectatorCam()
{
	this->name = "CondorEngine::SpectatorCam";
	this->camera = AddComponent<Camera>(new Camera());
}

void CondorEngine::SpectatorCam::Update()
{
	// TODO: spectator camera movement
}
