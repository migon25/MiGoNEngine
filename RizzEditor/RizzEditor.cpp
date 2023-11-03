#include "Layers.h"
#include "Model.h"
#include "..\RiZzEngine\RizzEngine.h"
#include <Windows.h>



/*The function returns whether this key is currently being pressed. We’re
creating a processInput function to keep all input code organized*/
void processInput(GLFWwindow* window);
static GLFWwindow* initGLFWwindowforOpengl();
int initGlad();


std::string GetHardwareInfo() {
    SYSTEM_INFO sysInfo;
    GetSystemInfo(&sysInfo);
    std::ostringstream info;
    info << "Processor Architecture: " << sysInfo.wProcessorArchitecture << std::endl;
    info << "Number of Processors: " << sysInfo.dwNumberOfProcessors << std::endl;
    info << "Page Size: " << sysInfo.dwPageSize << " bytes" << std::endl;
    return info.str();
}

std::vector<GameObject*> GameObjects;
std::vector<Model*> objectModels;

int main() {

	auto window = initGLFWwindowforOpengl();

	initGlad();

	// Specify the viewport of OpenGL in the window
	// from x = 0, y = 0, to x = WINDW_WIDTH, y = WINDOW_HEIGHT
	FBO fbo(WINDOW_WIDTH, WINDOW_HEIGHT);
	//glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
	glViewport(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT);
	glEnable(GL_DEPTH_TEST);

	Camera camera(WINDOW_WIDTH, WINDOW_HEIGHT, CAMERA_INIT_POS);
	Shader shaderProgram("default.vert", "default.frag");
	RizzEngine engine(GameObjects, objectModels);

	GameObject* cube = new GameObject();
	cube->path = "models/katana/scene.gltf";
	cube->name = "katana";
	GameObjects.push_back(cube);

	GameObject* bunny = new GameObject();
	bunny->path = "models/character/scene.gltf";
	bunny->name = "bunny";
	GameObjects.push_back(bunny);

	Layers layer(window,engine, camera, &fbo, GameObjects);

	// FPS Calculation
	static double lastTime = 0.0;
	static int frameCount = 0;
	double fps = 0.0;

	//MAin while loop. Window is open until the
	//ESCAPE button is pressed by the user
	while (!glfwWindowShouldClose(window))
	{
		double currentTime = glfwGetTime();
		double deltaTime = currentTime - lastTime;
		if ((glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS))
		{
			processInput(window); //process if the user has pressed ESCAPE button
		}
		layer.BeginLayer();
		fbo.Bind();
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); //Clean back buffer & assign new color to it

		camera.updateMatrix(45.0f, 0.1f, 1000.0f);

		static std::vector<float> fpsHistory;
		const int maxHistorySize = 100;  // Adjust as needed

		engine.Render(shaderProgram, camera);

		ImGui::Begin("Engine Information");
		ImGui::Text("FPS: %.2f", fps);

		// FPS Plot
		ImGui::PlotLines("FPS History", fpsHistory.data(), fpsHistory.size(), 0, NULL, 0.0f, 360.0f, ImVec2(0, 80));

		// Hardware Detection (Windows-specific)
		std::string hardwareInfo = GetHardwareInfo();
		ImGui::Text("%s", hardwareInfo.c_str());

		// Software Versions
		ImGui::Text("OpenGL Version: %s", glGetString(GL_VERSION));
		ImGui::Text("GLFW Version: %s", glfwGetVersionString());

		ImGui::End();

		fbo.Unbind();
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); //Clean back buffer & assign new color to it
		layer.Render();

		//Engine.model.Draw(shaderProgram, Engine.camera);
		layer.EndLayer();
		//Check and call events and swap buffers
		glfwSwapBuffers(window);
		glfwPollEvents();

		frameCount++;
		if (deltaTime >= 1.0) {
			fps = static_cast<double>(frameCount) / deltaTime;
			frameCount = 0;
			lastTime = currentTime;

			if (fpsHistory.size() >= maxHistorySize) {
				fpsHistory.erase(fpsHistory.begin());
			}
			fpsHistory.push_back(static_cast<float>(fps));
		}
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

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	glViewport(0, 0, width, height);
}