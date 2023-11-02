#include "PropertyPanel.h"

#include "imgui.h"
#include <stdio.h>

PropertyPanel::PropertyPanel(std::vector<GameObject*>& model) : Model(model)
{

}

PropertyPanel::~PropertyPanel()
{

}

void PropertyPanel::Render()
{
	static int counter = 0;
	ImGui::Begin("Properies", &active);// Create a window called "Hello, world!" and append into it.
	ImGui::Text("This is the property panel");// Edit bools storing our window open/close state
	ObjectSelection();
	if (Model.size() > 0)
	{
		ImGui::SliderFloat("scale", &Model[objectSelected]->scale, 0.0f, 1.0f);// Edit 1 float using a slider from 0.0f to 1.0f
	}
	if (ImGui::Button("Button")) // Buttons return true when clicked (most widgets return true when edited/activated)
	{
		counter++;
		printf("counter %i", counter);
	}
	ImGui::SameLine();
	ImGui::Text("counter = %d", counter);

	ImGui::End();
}

void PropertyPanel::ObjectSelection()
{
	ImGui::Begin("Objects");
	if (ImGui::Button("Add Object"))
	{
		wchar_t szFile[260];
		const wchar_t* filter = L"All\0*.*\0Text\0*.TXT\0";
		char output[256];
		sprintf_s(output, "%ws", szFile);
		printf(" %s\n", output);

		GameObject* obj = new GameObject();
		obj->path = output;
		//obj.modelColor = glm::vec3(1.0f, 1.0f, 0.2f);
		//obj.modelLineColor = glm::vec3(0.2f, 0.2f, 0.2f);

		char* token = NULL;
		char* name = NULL;
		char* next_token = NULL;
		const char* delimeter = "\\";
		token = strtok_s(output, delimeter, &next_token);
		while (token != NULL) {
			printf("%s\n", token);
			name = token;
			token = strtok_s(NULL, delimeter, &next_token);
		}
		printf("TOKEN %s\n", name);
		obj->name = name;
		Model.push_back(obj);
	}

	ImGui::Separator();
	static int selected = -1;
	for (int n = 0; n < Model.size(); n++)
	{
		char buf[256];
		sprintf_s(buf, Model[n]->name, n);
		if (ImGui::Selectable(buf, selected == n))
		{
			selected = n;
			std::cout << "Selected Object: " << selected << std::endl;
			objectSelected = n;
		}
	}

	ImGui::End();
}