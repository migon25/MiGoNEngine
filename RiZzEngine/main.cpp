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
{ //     COORDINATES     /        COLORS          /    TexCoord   /        NORMALS       //
	-0.5f, 0.0f,  0.5f,     0.83f, 0.70f, 0.44f, 	 0.0f, 0.0f,      0.0f, -1.0f, 0.0f, // Bottom side
	-0.5f, 0.0f, -0.5f,     0.83f, 0.70f, 0.44f,	 0.0f, 5.0f,      0.0f, -1.0f, 0.0f, // Bottom side
	 0.5f, 0.0f, -0.5f,     0.83f, 0.70f, 0.44f,	 5.0f, 5.0f,      0.0f, -1.0f, 0.0f, // Bottom side
	 0.5f, 0.0f,  0.5f,     0.83f, 0.70f, 0.44f,	 5.0f, 0.0f,      0.0f, -1.0f, 0.0f, // Bottom side

	-0.5f, 0.0f,  0.5f,     0.83f, 0.70f, 0.44f, 	 0.0f, 0.0f,     -0.8f, 0.5f,  0.0f, // Left Side
	-0.5f, 0.0f, -0.5f,     0.83f, 0.70f, 0.44f,	 5.0f, 0.0f,     -0.8f, 0.5f,  0.0f, // Left Side
	 0.0f, 0.8f,  0.0f,     0.92f, 0.86f, 0.76f,	 2.5f, 5.0f,     -0.8f, 0.5f,  0.0f, // Left Side

	-0.5f, 0.0f, -0.5f,     0.83f, 0.70f, 0.44f,	 5.0f, 0.0f,      0.0f, 0.5f, -0.8f, // Non-facing side
	 0.5f, 0.0f, -0.5f,     0.83f, 0.70f, 0.44f,	 0.0f, 0.0f,      0.0f, 0.5f, -0.8f, // Non-facing side
	 0.0f, 0.8f,  0.0f,     0.92f, 0.86f, 0.76f,	 2.5f, 5.0f,      0.0f, 0.5f, -0.8f, // Non-facing side

	 0.5f, 0.0f, -0.5f,     0.83f, 0.70f, 0.44f,	 0.0f, 0.0f,      0.8f, 0.5f,  0.0f, // Right side
	 0.5f, 0.0f,  0.5f,     0.83f, 0.70f, 0.44f,	 5.0f, 0.0f,      0.8f, 0.5f,  0.0f, // Right side
	 0.0f, 0.8f,  0.0f,     0.92f, 0.86f, 0.76f,	 2.5f, 5.0f,      0.8f, 0.5f,  0.0f, // Right side

	 0.5f, 0.0f,  0.5f,     0.83f, 0.70f, 0.44f,	 5.0f, 0.0f,      0.0f, 0.5f,  0.8f, // Facing side
	-0.5f, 0.0f,  0.5f,     0.83f, 0.70f, 0.44f, 	 0.0f, 0.0f,      0.0f, 0.5f,  0.8f, // Facing side
	 0.0f, 0.8f,  0.0f,     0.92f, 0.86f, 0.76f,	 2.5f, 5.0f,      0.0f, 0.5f,  0.8f  // Facing side
};

// Indices for vertices order
GLuint indices[] =
{
	0, 1, 2, // Bottom side
	0, 2, 3, // Bottom side
	4, 6, 5, // Left side
	7, 9, 8, // Non-facing side
	10, 12, 11, // Right side
	13, 15, 14 // Facing side
};

GLfloat lightVertices[] =
{ //     COORDINATES     //
	-0.1f, -0.1f,  0.1f,
	-0.1f, -0.1f, -0.1f,
	 0.1f, -0.1f, -0.1f,
	 0.1f, -0.1f,  0.1f,
	-0.1f,  0.1f,  0.1f,
	-0.1f,  0.1f, -0.1f,
	 0.1f,  0.1f, -0.1f,
	 0.1f,  0.1f,  0.1f
};

GLuint lightIndices[] =
{
	0, 1, 2,
	0, 2, 3,
	0, 4, 7,
	0, 7, 3,
	3, 7, 6,
	3, 6, 2,
	2, 6, 5,
	2, 5, 1,
	1, 5, 4,
	1, 4, 0,
	4, 5, 6,
	4, 6, 7
};

// Plane Vertices coordinates
GLfloat planeVertices[] =
{ //     COORDINATES     /        COLORS        /    TexCoord    /       NORMALS     //
	-1.0f, 0.0f,  1.0f,		0.0f, 0.0f, 0.0f,		0.0f, 0.0f,		0.0f, 1.0f, 0.0f,
	-1.0f, 0.0f, -1.0f,		0.0f, 0.0f, 0.0f,		0.0f, 1.0f,		0.0f, 1.0f, 0.0f,
	 1.0f, 0.0f, -1.0f,		0.0f, 0.0f, 0.0f,		1.0f, 1.0f,		0.0f, 1.0f, 0.0f,
	 1.0f, 0.0f,  1.0f,		0.0f, 0.0f, 0.0f,		1.0f, 0.0f,		0.0f, 1.0f, 0.0f
};

// Indices for plane vertices order
GLuint planeIndices[] =
{
	0, 1, 2,
	0, 2, 3
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


	//------------ VERTEX SHADERS CODE --------------------------------------//

	//------------------------Pyramid vertex code-----------------------//
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
	VAO1.LinkAttrib(VBO1, 0, 3, GL_FLOAT, 11 * sizeof(float), (void*)0);
	VAO1.LinkAttrib(VBO1, 1, 3, GL_FLOAT, 11 * sizeof(float), (void*)(3 * sizeof(float)));
	VAO1.LinkAttrib(VBO1, 2, 2, GL_FLOAT, 11 * sizeof(float), (void*)(6 * sizeof(float)));
	VAO1.LinkAttrib(VBO1, 3, 3, GL_FLOAT, 11 * sizeof(float), (void*)(8 * sizeof(float)));
	// Unbind ALL to prevent accidentaly modifying them
	VAO1.Unbind();
	VBO1.Unbind();
	EBO1.Unbind();

	//--------------------------Plane vertex code-----------------------//
	VAO VAOPlane;
	VAOPlane.Bind();

	VBO VBOPlane(planeVertices, sizeof(planeVertices));
	EBO EBOPlane(planeIndices, sizeof(planeIndices));

	VAOPlane.LinkAttrib(VBOPlane, 0, 3, GL_FLOAT, 11 * sizeof(float), (void*)0);
	VAOPlane.LinkAttrib(VBOPlane, 1, 3, GL_FLOAT, 11 * sizeof(float), (void*)(3 * sizeof(float)));
	VAOPlane.LinkAttrib(VBOPlane, 2, 2, GL_FLOAT, 11 * sizeof(float), (void*)(6 * sizeof(float)));
	VAOPlane.LinkAttrib(VBOPlane, 3, 3, GL_FLOAT, 11 * sizeof(float), (void*)(8 * sizeof(float)));

	VAOPlane.Unbind();
	VBOPlane.Unbind();
	EBOPlane.Unbind();

	//--------------------------Light vertex code-----------------------//
	Shader lightShader("light.vert", "light.frag");
	VAO VAOLight;
	VAOLight.Bind();

	VBO VBOLight(lightVertices, sizeof(lightVertices));
	EBO EBOLight(lightIndices, sizeof(lightIndices));

	VAOLight.LinkAttrib(VBOLight, 0, 3, GL_FLOAT, 3 * sizeof(float), (void*)0);

	VAOLight.Unbind();
	VBOLight.Unbind();
	EBOLight.Unbind();


	//light ----------------------------------
	
	// Light color
	glm::vec3 lightPos = glm::vec3(0.5f, 0.5f, 0.5f);
	glm::mat4 lightModel = glm::mat4(1.0f);
	float lightColor[4] = { 1.0f, 1.0f, 1.0f, 1.0f };
	float lightIntensity = 1.0f;

	lightModel = glm::translate(lightModel, lightPos);
	lightShader.Activate();
	glUniformMatrix4fv(glGetUniformLocation(lightShader.ID, "model"), 1, GL_FALSE, glm::value_ptr(lightModel));

	GLuint lightColorID = glGetUniformLocation(lightShader.ID, "lightColor");
	GLuint lightIntensityID = glGetUniformLocation(lightShader.ID, "intensity"); // Variable so we can change it in update real time

	//Pyramid --------------------------------

	glm::vec3 pyramidPos = glm::vec3(0.0f, 0.0f, 0.0f);
	glm::mat4 pyramidModel = glm::mat4(1.0f);
	pyramidModel = glm::translate(pyramidModel, pyramidPos);

	float scale = 1.0f;
	float color[4] = { 1.0f, 1.0f, 1.0f, 1.0f };
	float TexSize = 1.0f;

	shaderProgram.Activate();
	glUniformMatrix4fv(glGetUniformLocation(shaderProgram.ID, "model"), 1, GL_FALSE, glm::value_ptr(pyramidModel));
	GLuint colorFromLight = glGetUniformLocation(shaderProgram.ID, "lightColor");
	GLuint intensityFromLight = glGetUniformLocation(shaderProgram.ID, "intensity");
	glUniform3f(glGetUniformLocation(shaderProgram.ID, "lightPos"), lightPos.x, lightPos.y, lightPos.z);

	GLuint scaleID = glGetUniformLocation(shaderProgram.ID, "scale");

	GLuint colorID = glGetUniformLocation(shaderProgram.ID, "ImGuiColor");

	GLuint TexSizeID = glGetUniformLocation(shaderProgram.ID, "TexSize");

	Texture popcat("pop_cat.png", GL_TEXTURE_2D, 0, GL_RGBA, GL_UNSIGNED_BYTE);
	popcat.textUnit(shaderProgram, "tex0", 0);

	//Plane ----------------------------------
	glm::vec3 planePos = glm::vec3(0.0f, 0.0f, 0.0f);
	glm::mat4 planeModel = glm::mat4(1.0f);
	planeModel = glm::translate(planeModel, planePos);

	glUniformMatrix4fv(glGetUniformLocation(shaderProgram.ID, "model"), 1, GL_FALSE, glm::value_ptr(planeModel));
	glUniform3f(glGetUniformLocation(shaderProgram.ID, "lightPos"), lightPos.x, lightPos.y, lightPos.z);

	Texture floorTex("planks.png", GL_TEXTURE_2D, 0, GL_RGBA, GL_UNSIGNED_BYTE);
	floorTex.textUnit(shaderProgram, "tex0", 0);
	Texture floorSpec("planksSpec.png", GL_TEXTURE_2D, 1, GL_RED, GL_UNSIGNED_BYTE);
	floorSpec.textUnit(shaderProgram, "tex1", 1);


	//------------ VERTEX SHADERS CODE END ------------------------------------//

	//-------------------------IMGUI--------------------------------//

	// Initialize ImGui
	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO(); (void)io;
	ImGui::StyleColorsDark();
	ImGui_ImplGlfw_InitForOpenGL(window, true);
	ImGui_ImplOpenGL3_Init("#version 330");

	// Variables to be changed in the ImGUI window
	bool closeWindow = false;
	bool drawPyramid = false;

	//-------------------------IMGUI--------------------------------//

	glEnable(GL_DEPTH_TEST);

	Camera camera(WINDOW_WIDTH, WINDOW_HEIGHT, glm::vec3(0.0f, 0.5f, 2.0f));
	
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

		if (!io.WantCaptureMouse)
		{
			camera.Imputs(window);
		}
		camera.updateMatrix(45.0f, 0.1f, 100.0f);


		// Tell OpenGL which Shader program we want to use
		shaderProgram.Activate();
		// Exports the camera Position to the Fragment Shader for specular lighting
		glUniform3f(glGetUniformLocation(shaderProgram.ID, "camPos"), camera.Position.x, camera.Position.y, camera.Position.z);
		// Updates and exports the camera matrix to the Vertex Shader
		camera.Matrix(shaderProgram, "camMatrix");
		// Assigns a value to the uniform #NOTE: always after the shader is activated
		glUniform4f(colorFromLight, lightColor[0], lightColor[1], lightColor[2], lightColor[3]);
		glUniform1f(intensityFromLight, lightIntensity);
		glUniform1f(scaleID, scale);
		glUniform4f(colorID, color[0], color[1], color[2], color[3]);
		glUniform1f(TexSizeID, TexSize);
		// Bind the texture so it appears in the render
		popcat.Bind();
		// Bind the VAO so OpenGL knows how to use it
		VAO1.Bind();
		// Draw the triangle using the GL_TRIANGLES primitive
		if (drawPyramid)
		{
			glDrawElements(GL_TRIANGLES, sizeof(indices) / sizeof(int), GL_UNSIGNED_INT, 0);
		}

		floorTex.Bind();
		floorSpec.Bind();
		VAOPlane.Bind();
		glDrawElements(GL_TRIANGLES, sizeof(planeIndices) / sizeof(int), GL_UNSIGNED_INT, 0);


		// Tells OpenGL which Shader Program we want to use
		lightShader.Activate();
		// Export the camMatrix to the Vertex Shader of the light cube
		camera.Matrix(lightShader, "camMatrix");
		// Assigns a value to the uniform #NOTE: always after the shader is activated
		glUniform4f(lightColorID, lightColor[0], lightColor[1], lightColor[2], lightColor[3]);
		glUniform1f(lightIntensityID, lightIntensity);
		// Bind the VAO so OpenGL knows how to use it
		VAOLight.Bind();
		// Draw the triangle using the GL_TRIANGLES primitive
		glDrawElements(GL_TRIANGLES, sizeof(lightIndices) / sizeof(int), GL_UNSIGNED_INT, 0);


		//---------------------------- IMGUI STUFF ---------------------------//
		// Tell OpenGL a new frame is about to begin
		ImGui_ImplOpenGL3_NewFrame();
		ImGui_ImplGlfw_NewFrame();
		ImGui::NewFrame();

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
		// Slider for Texture Size
		ImGui::SliderFloat("Texture Scale", &TexSize, 0.5f, 100.0f);
		// Slider for light intensity
		ImGui::SliderFloat("Light intensity", &lightIntensity, 0.0f, 1.0f);
		// Fancy color editor that appears in the window
		ImGui::ColorEdit4("Color", color);
		// Fancy color editor for lights
		ImGui::ColorEdit4("Light Color", lightColor);
		// Ends the window
		ImGui::End();

		// Renders the ImGUI elements
		ImGui::Render();
		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
		//---------------------------- IMGUI STUFF ---------------------------//

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
	VAOLight.Delete();
	VBOLight.Delete();
	EBOLight.Delete();
	VAOPlane.Delete();
	VBOPlane.Delete();
	EBOPlane.Delete();
	floorTex.Delete();
	floorSpec.Delete();
	shaderProgram.Delete();
	lightShader.Delete();

	//Delete window before exiting the program
	glfwDestroyWindow(window);
	glfwTerminate();

	return 0;
}