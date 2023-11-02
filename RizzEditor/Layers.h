#ifndef LAYERS_CLASS_H
#define LAYERS_CLASS_H

#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"
#include "..\RiZzEngine\RizzEngine.h"

#include "PropertyPanel.h"

class Layers
{
public:
	glm::vec4 clear_color = glm::vec4(0.1f, 0.1f, 0.1f, 1.0f);
	Layers(GLFWwindow* window, Camera& camera, FBO* frameBuffer, std::vector<GameObject*>& model);

	void Render();
	void BeginLayer();
	void EndLayer();


protected:
	void AppMainMenuBar();
	void CreatePanels();
	Camera& camera;
	GLFWwindow* window;
	FBO* fbo;
	std::vector<GameObject*>& Model;
	std::unique_ptr<Panel> m_PropertyPanel;

	std::vector<Panel*> panels;
};

#endif //LAYERS_CLASS_H