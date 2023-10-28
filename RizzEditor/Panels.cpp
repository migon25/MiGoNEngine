#include "Panels.h"

Panels::Panels(GLFWwindow* window)
{
	// Setup Dear ImGui context
	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO(); (void)io;
	io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;     // Enable Keyboard Controls
	io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;      // Enable Gamepad Controls

	Panels::io = &io;
	// Setup Dear ImGui style
	ImGui::StyleColorsDark();
	//ImGui::StyleColorsLight();

	// Setup Platform/Renderer backends
	ImGui_ImplGlfw_InitForOpenGL(window, true);
	ImGui_ImplOpenGL3_Init("#version 130");
}

void Panels::Render(RizzEngine& Engine)
{
	ImGui_ImplOpenGL3_NewFrame();
	ImGui_ImplGlfw_NewFrame();
	ImGui::NewFrame();

	{
		static int counter = 0;

		ImGui::Begin("Hello, world!");                          // Create a window called "Hello, world!" and append into it.

		ImGui::Text("This is some useful text.");              // Edit bools storing our window open/close state

		ImGui::SliderFloat("float", (float*)&Engine.scale, 0.0f, 1.0f);            // Edit 1 float using a slider from 0.0f to 1.0f
		ImGui::ColorEdit3("clear color", (float*)&Engine.lightColor); // Edit 3 floats representing a color

		if (ImGui::Button("Button")) {                           // Buttons return true when clicked (most widgets return true when edited/activated)
			counter++;
			printf("counter %i", counter);
		}
		ImGui::SameLine();
		ImGui::Text("counter = %d", counter);

		ImGui::End();
	}

	// Rendering
	ImGui::Render();
	glClearColor(clear_color.x * clear_color.w, clear_color.y * clear_color.w, clear_color.z * clear_color.w, clear_color.w);
	ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}