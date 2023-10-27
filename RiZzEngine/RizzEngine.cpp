#include "RizzEngine.h"
#include "Globals.h"
#include "Model.h"

RizzEngine::RizzEngine()
{

}

void RizzEngine::LoadModels()
{

	Model model("models/bunny/scene.gltf");
	Model model1("models/map/scene.gltf");

	RizzEngine::model.push_back(model);
	RizzEngine::model.push_back(model1);
}

void RizzEngine::Render()
{
	Shader shaderProgram("default.vert", "default.frag");

	// Take care of all the light related things
	glm::vec4 lightColor = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f);
	glm::vec3 lightPos = glm::vec3(0.5f, 0.5f, 0.5f);
	glm::mat4 lightModel = glm::mat4(1.0f);
	lightModel = glm::translate(lightModel, lightPos);

	shaderProgram.Activate();
	glUniform4f(glGetUniformLocation(shaderProgram.ID, "lightColor"), lightColor.x, lightColor.y, lightColor.z, lightColor.w);
	glUniform3f(glGetUniformLocation(shaderProgram.ID, "lightPos"), lightPos.x, lightPos.y, lightPos.z);

		// Go over all meshes and draw each one
	for (unsigned int i = 0; i < model.size(); i++)
	{
		model[i].Model::Draw(shaderProgram, camera);
	}
}