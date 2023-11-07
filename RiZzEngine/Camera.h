#ifndef CAMERA_CLASS_H
#define CAMERA_CLASS_H

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtx/rotate_vector.hpp>
#include <glm/gtx/vector_angle.hpp>
#include <glm/gtx/quaternion.hpp>
#include <glm/gtc/quaternion.hpp>

#include "shaderClass.h"
#include "GameObject.h"
#include "Globals.h"
#include <vector>

class Camera
{
public:
	glm::vec3 Position;
	glm::vec3 Orientation = glm::vec3(0.0f, 0.0f, -1.0f);
	glm::vec3 Up = glm::vec3(0.0f, 1.0f, 0.0f);
	glm::vec3 flppedOrientation = glm::vec3(0.0f, -1.0f, 0.0f);
	glm::mat4 cameraMatrix = glm::mat4(1.0f);
	glm::vec2 smoothedMouseInput = glm::vec2(0.0f, 0.0f);

	bool firstClick = true;
	bool altPressed = false;
	bool focusOnObject = false;

	int width;
	int height;

	float FOV = 45.0f;
	float nearPlane = 0.1f;
	float farPlane = 1000.0f;
	float speed = 0.02f;
	float sensitivity = 1.0f;
	float smoothingFactor = 0.1f; 

	int objectSelected = 0; // Index of the currently targeted 3D object
	float orbitRadius = 30.0f;

	std::vector<GameObject*>& objects; // List of 3D objects to orbit

	Camera(int width, int height, glm::vec3 position, std::vector<GameObject*>& objectList);

	void updateMatrix(float FOVdeg);
	void Matrix(Shader& shader, const char* uniform);
	void updateCam();
	void ZoomIn(float zoomSpeed);
	void ZoomOut(float zoomSpeed);

	void Inputs(GLFWwindow* window);

	// Function to set the list of 3D objects
	void SetObjects(const std::vector<GameObject*>& objectList);
};

#endif
