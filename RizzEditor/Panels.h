#ifndef PANELS_CLASS_H
#define PANELS_CLASS_H

#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"
#include "..\RiZzEngine\RizzEngine.h"

class Panels
{
public:
	ImGuiIO* io;
	glm::vec4 clear_color = glm::vec4(0.1f, 0.1f, 0.1f, 1.0f);
	Panels(GLFWwindow* window);
	void Render(RizzEngine& Engine);

};

#endif //PANELS_CLASS_H