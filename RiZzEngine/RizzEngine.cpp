#include "RizzEngine.h"
#include "Globals.h"
#include "Model.h"

RizzEngine::RizzEngine()
{

}

void RizzEngine::LoadModels()
{

	Model model("models/katana/scene.gltf");
	Model model1("models/bunny/scene.gltf");

	RizzEngine::model.push_back(model);
	RizzEngine::model.push_back(model1);
}

void RizzEngine::Render()
{
	Shader shaderProgram("default.vert", "default.frag");

	RizzEngine::shader.push_back(shaderProgram);

	// Take care of all the light related things
	glm::vec3 lightPos = glm::vec3(0.5f, 0.5f, 0.5f);
	glm::mat4 lightModel = glm::mat4(1.0f);
	lightModel = glm::translate(lightModel, lightPos);

	shaderProgram.Activate();
	glUniform4f(glGetUniformLocation(shaderProgram.ID, "lightColor"), lightColor[0], lightColor[1], lightColor[2], lightColor[3]);
	glUniform1f(glGetUniformLocation(shaderProgram.ID, "imguiScale"), scale);
	glUniform3f(glGetUniformLocation(shaderProgram.ID, "lightPos"), lightPos.x, lightPos.y, lightPos.z);

		// Go over all meshes and draw each one
	for (unsigned int i = 0; i < model.size(); i++)
	{
		model[i].Model::Draw(shaderProgram, camera);
	}

	glPolygonMode(GL_FRONT_AND_BACK, wireframeMode ? GL_LINE : GL_FILL);
}