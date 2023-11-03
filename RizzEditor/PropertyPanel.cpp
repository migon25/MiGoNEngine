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
	ImGui::Begin("Mesh properties", &active);// Create a window called "Hello, world!" and append into it.
	ObjectSelection();
	if (ImGui::BeginTabBar("##tabs", ImGuiTabBarFlags_None))
	{
		if (ImGui::BeginTabItem("Transform"))
		{
			if (Model.size() > 0)
			{
				if (ImGui::CollapsingHeader("Position"))
				{
					ImGui::DragFloat("X", &Model[objectSelected]->positionX, 0.1f, 0.0f, +FLT_MAX);
					ImGui::DragFloat("Y", &Model[objectSelected]->positionY, 0.1f, 0.0f, +FLT_MAX);
					ImGui::DragFloat("Z", &Model[objectSelected]->positionZ, 0.1f, 0.0f, +FLT_MAX);
					glm::mat4 translationMatrix = glm::mat4(1.0f); // Initialize as identity matrix
					translationMatrix = glm::translate(translationMatrix, glm::vec3(Model[objectSelected]->positionX, Model[objectSelected]->positionY, Model[objectSelected]->positionZ));
					Model[objectSelected]->objTranslation = translationMatrix;
				}

				if (ImGui::CollapsingHeader("Scale"))
				{
					ImGui::DragFloat("scaleObject", &Model[objectSelected]->scaleObject, 0.1f, 0.0f, +FLT_MAX);

					ImGui::DragFloat("Scale X", &Model[objectSelected]->scaleX, 0.1f, 0.0f, +FLT_MAX);
					ImGui::DragFloat("Scale Y", &Model[objectSelected]->scaleY, 0.1f, 0.0f, +FLT_MAX);
					ImGui::DragFloat("Scale Z", &Model[objectSelected]->scaleZ, 0.1f, 0.0f, +FLT_MAX);
				}

				if (ImGui::CollapsingHeader("Rotation"))
				{
					ImGui::DragFloat("Pitch", &Model[objectSelected]->pitch, 0.5f, -FLT_MAX, +FLT_MAX);
					ImGui::DragFloat("Yaw", &Model[objectSelected]->yaw, 0.5f, -FLT_MAX, +FLT_MAX);
					ImGui::DragFloat("Roll", &Model[objectSelected]->roll, 0.5f, -FLT_MAX, +FLT_MAX);

					glm::mat4 rotationMatrix(1.0f);

					rotationMatrix = glm::rotate(rotationMatrix, glm::radians(Model[objectSelected]->pitch), glm::vec3(1.0f, 0.0f, 0.0f));
					rotationMatrix = glm::rotate(rotationMatrix, glm::radians(Model[objectSelected]->yaw), glm::vec3(0.0f, 1.0f, 0.0f));
					rotationMatrix = glm::rotate(rotationMatrix, glm::radians(Model[objectSelected]->roll), glm::vec3(0.0f, 0.0f, 1.0f));
					
					Model[objectSelected]->objRotation = rotationMatrix;
				}
			}
			ImGui::EndTabItem();
		}
		if (ImGui::BeginTabItem("Texture"))
		{
			ImGui::EndTabItem();
		}
		ImGui::EndTabBar();
	}
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