#include "PropertyPanel.h"

#include "imgui.h"
#include <stdio.h>

PropertyPanel::PropertyPanel(RizzEngine& engine) : Engine(engine)
{

}

PropertyPanel::~PropertyPanel()
{

}

void PropertyPanel::Render()
{
	static int counter = 0;
	ImGui::Begin("Properies", &active);// Create a window called "Hello, world!" and append into it.
	ImGui::Text("This is some useful text.");// Edit bools storing our window open/close state

	ImGui::SliderFloat("scale", (float*)&Engine.scale, 0.0f, 1.0f);// Edit 1 float using a slider from 0.0f to 1.0f
	ImGui::ColorEdit3("light color", (float*)&Engine.lightColor); // Edit 3 floats representing a color

	if (ImGui::Button("Button")) // Buttons return true when clicked (most widgets return true when edited/activated)
	{
		counter++;
		printf("counter %i", counter);
	}
	ImGui::SameLine();
	ImGui::Text("counter = %d", counter);

	ImGui::Checkbox("WireFrame Mode", &Engine.wireframeMode);

	ImGui::End();
}