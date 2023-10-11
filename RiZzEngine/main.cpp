#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include"imgui.h"
#include"imgui_impl_glfw.h"
#include"imgui_impl_opengl3.h"

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <stb/stb_image.h>

#include "Texture.h"
#include "shaderClass.h"
#include "VAO.h"
#include "VBO.h"
#include "EBO.h"
#include "Camera.h"

#define WINDOW_WIDTH  800
#define WINDOW_HEIGHT 800
#define WINDOW_TITLE "RIZZ ENGINE"


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

//Vertices Coordinates
GLfloat vertices[] =
{ //      COORDNATES       /        COLORS        /    TEXTURE COORD
	-0.5f,  0.0f,  0.5f,         0.0f, 1.0f, 0.0f,	  0.0f, 0.0f,      //Lower Left corner
	-0.5f,  0.0f, -0.5f,         1.0f, 0.0f, 0.0f,    5.0f, 0.0f,      //Lower Rigth corner
	 0.5f,  0.0f, -0.5f,         0.0f, 0.0f, 1.0f,    0.0f, 0.0f,      //Upper corner
	 0.5f,  0.0f,  0.5f,         0.0f, 0.5f, 0.5f,    5.0f, 0.0f,      //Upper Left
     0.0f,  0.8f,  0.0f,         0.0f, 0.5f, 0.5f,    2.5f, 5.0f       //Upper Left
};

// Indices for vertices order
GLuint indices[] =
{
	0, 1, 2,
	0, 2, 3,
	0, 1, 4,
	1, 2, 4,
	2, 3, 4,
	3, 0, 4
};

int main() {

	//initializing GLFW
	glfwInit();

	//Tell GLFW what version of OpenGL we are using
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
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
		return -1;
	}

	//Introduce the window into current context
	glfwMakeContextCurrent(window);

	//Error check for GLAD initialization
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		printf("Failed to initialize GLAD");
		return -1;
	}

	// Load GLAD so it configures OpenGL
	gladLoadGL();
	// Specify the viewport of OpenGL in the window
	// from x = 0, y = 0, to x = WINDW_WIDTH, y = WINDOW_HEIGHT
	glViewport(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT);


	//------------ VERTEX SHADERS CODE FINAL------------------------//

	// Create shader objects using sahders default.vert and default.frag
	Shader shaderProgram("default.vert", "default.frag");

	// Generate Vertex Array Objects and binds it
	VAO VAO1;
	VAO1.Bind();

	// Generate Vertex Buffer Objects and links it to vertices
	VBO VBO1(vertices, sizeof(vertices));
	// Generate Element Buffer Objects and links it to indices
	EBO EBO1(indices, sizeof(indices));

	// Links VBO attributes such as coordinates and colors to VAO
	VAO1.LinkAttrib(VBO1, 0, 3, GL_FLOAT, 8 * sizeof(float), (void*)0);
	VAO1.LinkAttrib(VBO1, 1, 3, GL_FLOAT, 8 * sizeof(float), (void*)(3*sizeof(float)));
	VAO1.LinkAttrib(VBO1, 2, 2, GL_FLOAT, 8 * sizeof(float), (void*)(6 * sizeof(float)));
	// Unbind ALL to prevent accidentaly modifying them
	VAO1.Unbind();
	VBO1.Unbind();
	EBO1.Unbind();

	// Initialize ImGUI
	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO(); (void)io;
	ImGui::StyleColorsDark();
	ImGui_ImplGlfw_InitForOpenGL(window, true);
	ImGui_ImplOpenGL3_Init("#version 330");

	// Variables to be changed in the ImGUI window
	bool closeWindow = false;
	bool drawPyramid = true;
	float scale = 1.0f;
	GLuint scaleID = glGetUniformLocation(shaderProgram.ID, "scale");

	float color[4] = { 1.0f, 1.0f, 1.0f, 1.0f };
	GLuint colorID = glGetUniformLocation(shaderProgram.ID, "ImGuiColor");


	// Create texture
	Texture popcat("pop_cat.png", GL_TEXTURE_2D, GL_TEXTURE0, GL_RGBA, GL_UNSIGNED_BYTE);
	popcat.textUnit(shaderProgram, "tex0", 0);

	//------------ VERTEX SHADERS CODE FINAL------------------------//

	glEnable(GL_DEPTH_TEST);

	Camera camera(WINDOW_WIDTH, WINDOW_HEIGHT, glm::vec3(2.0f, 2.0f, 2.0f), glm::vec3(-1.0f, -1.0f, -1.0f));
	
	//MAin while loop. Window is open until the
	//ESCAPE button is pressed by the user
	while (!glfwWindowShouldClose(window))
	{
		if (closeWindow == true || (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS))
		{
			processInput(window); //process if the user has pressed ESCAPE button
		}

		//RENDERING------------------------------------------------------------//
		glClearColor(0.1f, 0.1f, 0.1f, 1.0f);    //Specify color of bg
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); //Clean back buffer & assign new color to it

		// Tell OpenGL a new frame is about to begin
		ImGui_ImplOpenGL3_NewFrame();
		ImGui_ImplGlfw_NewFrame();
		ImGui::NewFrame();

		// Tell OpenGL which Shader program we want to use
		shaderProgram.Activate();

		// Assigns a value to the uniform;
		glUniform1f(scaleID, scale);
		glUniform4f(colorID, color[0], color[1], color[2], color[3]);

		if (!io.WantCaptureMouse)
		{
			camera.Imputs(window);
		}
		camera.Matrix(45.0f, 0.1f, 100.0f, shaderProgram, "camMatrix");

		// Bind the texture so it appears in the render
		popcat.Bind();

		// Bind the VAO so OpenGL knows how to use it
		VAO1.Bind();
		// Draw the triangle using the GL_TRIANGLES primitive
		if (drawPyramid)
		{
			glDrawElements(GL_TRIANGLES, sizeof(indices) / sizeof(int), GL_UNSIGNED_INT, 0);
		}

		// ImGUI window creation
		ImGui::Begin("ImGUI Window Test");
		// Checkbox that appears in the window
		ImGui::Checkbox("CLOSE PROGRAM", &closeWindow);
		// Text that appears in the window
		ImGui::Text("SIMPLE TEXT");
		// Checkbox that appears in the window
		ImGui::Checkbox("Draw Pyramid", &drawPyramid);
		// Slider that appears in the window
		ImGui::SliderFloat("scale", &scale, 0.5f, 2.0f);
		// Fancy color editor that appears in the window
		ImGui::ColorEdit4("Color", color);
		// Ends the window
		ImGui::End();

		// Renders the ImGUI elements
		ImGui::Render();
		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

		//RENDERING END ------------------------------------------------------//

		//Check and call events and swap buffers
		glfwSwapBuffers(window);
		glfwPollEvents();
	};

	//------------------------ END OF THE PROGRAM B4 EXITING ---------------//

	// Deletes all ImGUI instances
	ImGui_ImplOpenGL3_Shutdown();
	ImGui_ImplGlfw_Shutdown();
	ImGui::DestroyContext();

	//Deleting Vertex Shaders
	VAO1.Delete();
	VBO1.Delete();
	EBO1.Delete();
	popcat.Delete();
	shaderProgram.Delete();

	//Delete window before exiting the program
	glfwDestroyWindow(window);
	glfwTerminate();

	return 0;
}