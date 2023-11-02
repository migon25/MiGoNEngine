#include "RizzEngine.h"
#include "Globals.h"
#include "Model.h"

RizzEngine::RizzEngine(std::vector<GameObject*>& gameObject, std::vector<Model*>& objectModels) : m_gameObject(gameObject), model(objectModels)
{

}

void RizzEngine::LoadModels()
{
	//Model model("models/katana/scene.gltf");
	//Model model1("models/bunny/scene.gltf");

	//RizzEngine::model.push_back(model);
	//RizzEngine::model.push_back(model1);

	for (int i = 0; i < m_gameObject.size(); i++)
	{
		if (!m_gameObject[i]->modelDefined)
		{
			Model* model = new Model(m_gameObject[i]);
			RizzEngine::model.push_back(model);
			m_gameObject[i]->modelDefined = true;
		}
	}
}

void RizzEngine::Render(Shader& shader, Camera& camera)
{
	LoadModels();

	// Take care of all the light related things
	glm::vec3 lightPos = glm::vec3(0.5f, 0.5f, 0.5f);
	glm::mat4 lightModel = glm::mat4(1.0f);
	lightModel = glm::translate(lightModel, lightPos);

		// Go over all meshes and draw each one
	for (unsigned int i = 0; i < model.size(); i++)
	{
		shader.Activate();
		glUniformMatrix4fv(glGetUniformLocation(shader.ID, "model"), 1, GL_FALSE, glm::value_ptr(m_gameObject[i]->objModel));
		glUniform4f(glGetUniformLocation(shader.ID, "lightColor"), lightColor[0], lightColor[1], lightColor[2], lightColor[3]);
		glUniform1f(glGetUniformLocation(shader.ID, "imguiScale"), scale);
		glUniform3f(glGetUniformLocation(shader.ID, "lightPos"), lightPos.x, lightPos.y, lightPos.z);

		model[i]->Model::Draw(shader, camera);
	}

	glPolygonMode(GL_FRONT_AND_BACK, wireframeMode ? GL_LINE : GL_FILL);
}