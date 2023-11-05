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
	glm::quat orientation;

	glm::mat4 objModel = glm::mat4(1.0f);
	float scaleObject = 1.0f;

	glm::mat4 objScale = glm::mat4(1.0f);
	float scaleX = 1.0f;
	float scaleY = 1.0f;
	float scaleZ = 1.0f;

	glm::mat4 objRotation = glm::mat4(1.0f);
	float pitch = 0.0f;
	float yaw = 0.0f;
	float roll = 0.0f;

	glm::mat4 objTranslation = glm::mat4(1.0f);
	float positionX = 0.0f;
	float positionY = 0.0f;
	float positionZ = 0.0f;

	// Method to get the position of the object
	glm::vec3 GetPosition() const {
		return glm::vec3(positionX, positionY, positionZ);
	}

	// Method to get the orientation of the object
	glm::vec3 GetOrientation() const {
		return glm::vec3(pitch, yaw, roll);
	}

	void SetOrientation(const glm::quat& newOrientation) {
		orientation = newOrientation;
	}
};

#endif //GAME_OBJECT_H