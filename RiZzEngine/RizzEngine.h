#ifndef RIZZ_ENGINE_H
#define RIZZ_ENGINE_H

#include "Camera.h"
#include "Model.h"
#include "GameObject.h"

class RizzEngine
{
public:
	std::vector<Model*>& model;
	std::vector<GameObject*>& m_gameObject;

	float lightColor[4] = { 1.0f, 1.0f, 1.0f, 1.0f };
	float scale = 1.0f;
	bool wireframeMode = false;

	RizzEngine(std::vector<GameObject*>& objectStructures, std::vector<Model*>& objectModels);
	void LoadModels();
	void Render(Shader& shader, Camera& camera);
};

#endif //RIZZ_ENGINE_H