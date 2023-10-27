#ifndef RIZZ_ENGINE_H
#define RIZZ_ENGINE_H

#include "Camera.h"
#include "Model.h"

class RizzEngine
{
public:
	std::vector<Model> model;
	Camera camera;
	RizzEngine();
	void LoadModels();
	void Render();
};

#endif //RIZZ_ENGINE_H