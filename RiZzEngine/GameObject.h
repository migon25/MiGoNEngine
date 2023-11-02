#ifndef GAME_OBJECT_H
#define GAME_OBJECT_H

#include "glm/glm.hpp"

struct GameObject
{
	bool modelDefined = false;
	bool AABB = false;

	const char* path;
	const char* name;
	float scale;
	glm::vec3 modelColor = glm::vec3(0.5f, 0.5f, 0.5f);
	glm::vec3 modelLineColor = glm::vec3(0.2f, 0.2f, 0.2f);
	glm::mat4 objModel = glm::mat4(1.0f);
	glm::vec3 objRotation = glm::vec3(0.0f);
	glm::vec3 objTranslation = glm::vec3(0.0f);
};

#endif //GAME_OBJECT_H