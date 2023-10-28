#include "Panels.h"
#include "Model.h"
#include "..\RiZzEngine\RizzEngine.h"


void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	glViewport(0, 0, width, height);
}

/*The function returns whether this key is currently being pressed. We’re
creating a processInput function to keep all input code organized*/
void processInput(GLFWwindow* window)
{
	glfwSetWindowShouldClose(window, true);
}

static GLFWwindow* initGLFWwindowforOpengl()
{
	//initializing GLFW
	glfwInit();

	//Tell GLFW what version of OpenGL we are using
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);  // 3.2+ only
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);            // 3.0+ only
	//Tell GLFW that we are using CORE profile
	//so that means we only have the modern
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	//glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

	//CREATION OF THE WINDOW WITH THE GLOBAL PARAMETERS
	//WE HAVE SET FOR WIDTH & HEIGHT AND THE TITLE 
	GLFWwindow* window = glfwCreateWindow(WINDOW_WIDTH, WINDOW_HEIGHT, WINDOW_TITLE, NULL, NULL);
	//Check for error in creating the window
	if (window == NULL)
	{
		printf("Failed to create GLFW window");
		glfwTerminate();
	}

	//Introduce the window into current context
	glfwMakeContextCurrent(window);

	return window;
}

int initGlad()
{
	//Error check for GLAD initialization
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		printf("Failed to initialize GLAD");
		return -1;
	}
	// Load GLAD so it configures OpenGL
	gladLoadGL();

	return 1;
}

int main() {

	auto window = initGLFWwindowforOpengl();

	initGlad();

	// Specify the viewport of OpenGL in the window
	// from x = 0, y = 0, to x = WINDW_WIDTH, y = WINDOW_HEIGHT
	glViewport(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT);
	glEnable(GL_DEPTH_TEST);

	RizzEngine Engine;
	Engine.LoadModels();


	Panels panel(window);

	//MAin while loop. Window is open until the
	//ESCAPE button is pressed by the user
	while (!glfwWindowShouldClose(window))
	{
		if ((glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS))
		{
			processInput(window); //process if the user has pressed ESCAPE button
		}

		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); //Clean back buffer & assign new color to it

		if(!panel.io->WantCaptureMouse)
			Engine.camera.Imputs(window);
		Engine.camera.updateMatrix(45.0f, 0.1f, 1000.0f);
		//glClearColor(0.1f,0.1f,0.1f,1.0f);
		Engine.Render();
		panel.Render(Engine);

		//Engine.model.Draw(shaderProgram, Engine.camera);

		//Check and call events and swap buffers
		glfwSwapBuffers(window);
		glfwPollEvents();
	};

	//Deleting Vertex Shaders
	//shaderProgram.Delete();

	//Delete window before exiting the program
	ImGui_ImplOpenGL3_Shutdown();
	ImGui_ImplGlfw_Shutdown();
	ImGui::DestroyContext();
	glfwDestroyWindow(window);
	glfwTerminate();

	return 0;
}