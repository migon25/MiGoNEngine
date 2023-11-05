#include "Camera.h"

Camera::Camera(int width, int height, glm::vec3 position, std::vector<GameObject*>& objectList) : objects(objectList)
{
	Camera::width = width;
	Camera::height = height;
	Position = position;

	objects = {}; // Initialize your list of 3D objects
}

void Camera::updateMatrix(float FOVdeg, float nearPlane, float farPlane)
{
	glm::mat4 view = glm::mat4(1.0f);
	glm::mat4 proj = glm::mat4(1.0f);

	view = glm::lookAt(Position, Position + Orientation, Up);
	proj = glm::perspective(glm::radians(FOVdeg), (float)(width / height), nearPlane, farPlane);

	cameraMatrix = proj * view;
}

void Camera::Matrix(Shader& shader, const char* uniform)
{
	glUniformMatrix4fv(glGetUniformLocation(shader.ID, uniform), 1, GL_FALSE, glm::value_ptr(cameraMatrix));
}

void Camera::Imputs(GLFWwindow* window)
{
	double mouseX, mouseY;
	glfwGetCursorPos(window, &mouseX, &mouseY);
	static double lastMouseX = mouseX;
	static double lastMouseY = mouseY;

	double lastFrameTime = glfwGetTime();

	// In your update loop:
	double currentTime = glfwGetTime();
	double deltaTime = currentTime - lastFrameTime;

	if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS)
	{
		// Calculate the change in mouse position
		double deltaX = mouseX - lastMouseX;
		double deltaY = mouseY - lastMouseY;

		smoothedMouseInput.x = smoothedMouseInput.x + smoothingFactor * (deltaX - smoothedMouseInput.x);
		smoothedMouseInput.y = smoothedMouseInput.y + smoothingFactor * (deltaY - smoothedMouseInput.y);

		// Convert rotation angles to radians
		float pitch = -static_cast<float>(smoothedMouseInput.y) * sensitivity;
		float yaw = -static_cast<float>(smoothedMouseInput.x) * sensitivity;

		// Implement constraints to avoid flipping (check if you've crossed a threshold)
		const float maxPitch = glm::radians(89.0f); // Adjust this angle as needed
		const float minPitch = -maxPitch;
		pitch = glm::clamp(pitch, minPitch, maxPitch);

		if (pitch < maxPitch)
		{
			degrees = true;
			objects[objectSelected]->GetOrientation() = glm::rotate(objects[objectSelected]->GetOrientation(), glm::radians(180.0f), Up);
		}
		else if (pitch > minPitch)
		{
			degrees = false;
			objects[objectSelected]->GetOrientation() = glm::rotate(objects[objectSelected]->GetOrientation(), glm::radians(180.0f), flppedOrientation);
		}
		// Calculate the quaternion for pitch (up/down rotation)
		glm::quat pitchQuat = glm::angleAxis(glm::radians(pitch), glm::normalize(glm::cross(degrees ? Orientation : flppedOrientation, degrees ? Up : Down)));

		// Calculate the quaternion for yaw (left/right rotation)
		glm::quat yawQuat = glm::angleAxis(glm::radians(yaw), degrees ? Up : Down);

		// Combine the pitch and yaw rotations by multiplying the quaternions
		glm::quat orientationChange = pitchQuat * yawQuat;

		// Apply the orientation change to the Orientation vector
		Orientation = glm::rotate(orientationChange, degrees ? Orientation : flppedOrientation);

		// Calculate the rotation angle around the "Up" axis for the object
		float objectYaw = yaw; // Adjust as needed for the desired rotation axis

		// Update the object's orientation based on camera rotation
		glm::quat objectOrientation = objects[objectSelected]->GetOrientation();
		glm::quat newObjectOrientation = glm::angleAxis(objectYaw, degrees ? Up : Down);

		// Smoothly interpolate the orientation to avoid sudden flips
		const float interpolationFactor = 0.05f;
		objectOrientation = glm::slerp(objectOrientation, newObjectOrientation, interpolationFactor);
		objects[objectSelected]->SetOrientation(objectOrientation);
	}
	else if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_RELEASE)
	{
		// Unhides cursor since camera is not looking around anymore
		glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
		// Makes sure the next time the camera looks around it doesn't jump
		firstClick = true;
	}
	
	if (glfwGetKey(window, GLFW_KEY_L) == GLFW_PRESS)
	{
		// Switch to the next object in your list
		objectSelected = (objectSelected + 1) % objects.size();
	}
	if (glfwGetKey(window, GLFW_KEY_K) == GLFW_PRESS)
	{
		// Switch to the previous object in your list
		objectSelected = (objectSelected - 1 + objects.size()) % objects.size();
	}

	// Update the view matrix
	updateMatrix(45.0f, 0.1f, 1000.0f);

	lastMouseX = mouseX;
	lastMouseY = mouseY;

	// Define a factor to control the smoothness of interpolation
	float interpolationFactor = 0.05f; // Adjust this value for the desired speed of transition

	// Interpolate the camera's position smoothly towards the target position
	Position = glm::mix(Position, -objects[objectSelected]->GetPosition() - orbitRadius * Orientation, interpolationFactor);

	lastFrameTime = currentTime; // Update last frame time
}

void Camera::SetObjects(const std::vector<GameObject*>& objectList)
{
	objects = objectList;
}