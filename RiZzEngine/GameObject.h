#ifndef GAME_OBJECT_H
#define GAME_OBJECT_H

#include "glm/glm.hpp"
#include <glm/gtc/matrix_transform.hpp>

struct GameObject
{
	bool modelDefined = false;
	bool AABB = false;

	const char* path;
	const char* name;

	glm::vec3 modelColor = glm::vec3(0.5f, 0.5f, 0.5f);
	glm::vec3 modelLineColor = glm::vec3(0.2f, 0.2f, 0.2f);

	glm::mat4 objModel = glm::mat4(1.0f);
	float scaleObject = 1.0f;

	glm::mat4 objScale = glm::mat4(1.0f);
	float scaleX = 1.0f;
	float scaleY = 1.0f;
	float scaleZ = 1.0f;

	glm::mat4 objRotation = glm::mat4(1.0f);
	float pitch = 1.0f;
	float yaw = 1.0f;
	float roll = 1.0f;

	glm::mat4 objTranslation = glm::mat4(1.0f);
	float positionX = 1.0f;
	float positionY = 1.0f;
	float positionZ = 1.0f;
};

#endif //GAME_OBJECT_H