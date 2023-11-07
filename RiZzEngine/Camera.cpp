#include "Camera.h"

Camera::Camera(int width, int height, glm::vec3 position, std::vector<GameObject*>& objectList) : objects(objectList)
{
	Camera::width = width;
	Camera::height = height;
	Position = position;

	objects = {}; // Initialize your list of 3D objects
}

void Camera::updateMatrix(float FOVdeg)
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

void Camera::Inputs(GLFWwindow* window)
{
	double mouseX, mouseY;
	glfwGetCursorPos(window, &mouseX, &mouseY);
	static double lastMouseX = mouseX;
	static double lastMouseY = mouseY;

	if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_RIGHT) == GLFW_PRESS)
	{
		focusOnObject = false;
		firstClick = false;
		// Calculate the change in mouse position
		double deltaX = mouseX - lastMouseX;
		double deltaY = mouseY - lastMouseY;

		smoothedMouseInput.x = smoothedMouseInput.x + smoothingFactor * (deltaX - smoothedMouseInput.x);
		smoothedMouseInput.y = smoothedMouseInput.y + smoothingFactor * (deltaY - smoothedMouseInput.y);

		// Convert rotation angles to radians
		float pitch = -static_cast<float>(smoothedMouseInput.y) * sensitivity;
		float yaw = -static_cast<float>(smoothedMouseInput.x) * sensitivity;

		// Calculate the quaternion for pitch (up/down rotation)
		glm::quat pitchQuat = glm::angleAxis(glm::radians(pitch), glm::normalize(glm::cross(Orientation, Up)));

		// Calculate the quaternion for yaw (left/right rotation)
		glm::quat yawQuat = glm::angleAxis(glm::radians(yaw), Up);

		// Combine the pitch and yaw rotations by multiplying the quaternions
		glm::quat orientationChange = pitchQuat * yawQuat;

		// Apply the orientation change to the Orientation vector
		Orientation = glm::rotate(orientationChange, Orientation);

		// Calculate the rotation angle around the "Up" axis for the object
		float objectYaw = yaw; // Adjust as needed for the desired rotation axis

		// Update the object's orientation based on camera rotation
		glm::quat objectOrientation = objects[objectSelected]->GetOrientation();
		glm::quat newObjectOrientation = glm::angleAxis(objectYaw, Up);

		// Smoothly interpolate the orientation to avoid sudden flips
		const float interpolationFactor = 0.05f;
		objectOrientation = glm::slerp(objectOrientation, newObjectOrientation, interpolationFactor);
		objects[objectSelected]->SetOrientation(objectOrientation);

	}
	else if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS && altPressed == true)
	{
		focusOnObject = true;
		firstClick = false;

		// Calculate the change in mouse position
		double deltaX = mouseX - lastMouseX;
		double deltaY = mouseY - lastMouseY;

		smoothedMouseInput.x = smoothedMouseInput.x + smoothingFactor * (deltaX - smoothedMouseInput.x);
		smoothedMouseInput.y = smoothedMouseInput.y + smoothingFactor * (deltaY - smoothedMouseInput.y);

		// Convert rotation angles to radians
		float pitch = -static_cast<float>(smoothedMouseInput.y) * sensitivity;
		float yaw = -static_cast<float>(smoothedMouseInput.x) * sensitivity;

		// Calculate the quaternion for pitch (up/down rotation)
		glm::quat pitchQuat = glm::angleAxis(glm::radians(pitch), glm::normalize(glm::cross(Orientation, Up)));

		// Calculate the quaternion for yaw (left/right rotation)
		glm::quat yawQuat = glm::angleAxis(glm::radians(yaw), Up);

		// Combine the pitch and yaw rotations by multiplying the quaternions
		glm::quat orientationChange = pitchQuat * yawQuat;

		// Apply the orientation change to the Orientation vector
		Orientation = glm::rotate(orientationChange, Orientation);

		// Calculate the rotation angle around the "Up" axis for the object
		float objectYaw = yaw; // Adjust as needed for the desired rotation axis

		// Update the object's orientation based on camera rotation
		glm::quat objectOrientation = objects[objectSelected]->GetOrientation();
		glm::quat newObjectOrientation = glm::angleAxis(objectYaw, Up);

		// Smoothly interpolate the orientation to avoid sudden flips
		const float interpolationFactor = 0.05f;
		objectOrientation = glm::slerp(objectOrientation, newObjectOrientation, interpolationFactor);
		objects[objectSelected]->SetOrientation(objectOrientation);

		updateCam();
	}
	else if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_RELEASE || glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_RIGHT) == GLFW_RELEASE)
	{
		// Makes sure the next time the camera looks around it doesn't jump
		firstClick = true;
	}

	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
	{
		focusOnObject = false;
		Position += speed * Orientation;
	}
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
	{
		focusOnObject = false;
		Position -= speed * Orientation;
	}
	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
	{
		focusOnObject = false;
		Position -= glm::normalize(glm::cross(Orientation, Up)) * speed;
	}
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
	{
		focusOnObject = false;
		Position += glm::normalize(glm::cross(Orientation, Up)) * speed;
	}
	if (glfwGetKey(window, GLFW_KEY_F) == GLFW_PRESS)
	{
		focusOnObject = true;
	}
	if(focusOnObject == true)
		updateCam();

	if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS)
	{
		focusOnObject = false;
		Position += speed * Up;
	}
	if (glfwGetKey(window, GLFW_KEY_LEFT_CONTROL) == GLFW_PRESS)
	{
		focusOnObject = false;
		Position -= speed * Up;
	}
	if (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS)
	{
		speed = 0.1f;
	}
	else if (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_RELEASE)
	{
		speed = 0.02f;
	}
	if (glfwGetKey(window, GLFW_KEY_LEFT_ALT) == GLFW_PRESS)
	{
		altPressed = true;
	}
	else
		altPressed = false;

	// Update the view matrix
	updateMatrix(FOV);

	lastMouseX = mouseX;
	lastMouseY = mouseY;

}

void Camera::ZoomIn(float zoomSpeed)
{
	FOV = FOV * zoomSpeed;
}

void Camera::ZoomOut(float zoomSpeed)
{
	FOV -= zoomSpeed;
}

void Camera::updateCam()
{	
	// Define a factor to control the smoothness of interpolation
	float interpolationFactor = 0.05f; // Adjust this value for the desired speed of transition

	// Interpolate the camera's position smoothly towards the target position
	if(focusOnObject == true)
		Position = glm::mix(Position, -objects[objectSelected]->GetPosition() - orbitRadius * Orientation, interpolationFactor);
}

void Camera::SetObjects(const std::vector<GameObject*>& objectList)
{
	objects = objectList;
}