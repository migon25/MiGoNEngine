#ifndef RIZZ_ENGINE_H
#define RIZZ_ENGINE_H

#include "Camera.h"
#include "Model.h"

class RizzEngine
{
public:
	std::vector<Model> model;
	std::vector<Shader> shader;

	float lightColor[4] = { 1.0f, 1.0f, 1.0f, 1.0f };
	float scale = 1.0f;
	bool wireframeMode = false;

	Camera& engineCamera;
	RizzEngine(Camera& camera);
	void LoadModels();
	void Render();
};

#endif //RIZZ_ENGINE_H