#include <stdlib.h>
#include <stdio.h>
#include <iostream>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "shaderClass.h"
#include "VAO.h"
#include "VBO.h"
#include "EBO.h"

#define WINDOW_WIDTH  800
#define WINDOW_HEIGHT 800
#define WINDOW_TITLE "RIZZ ENGINE TEST"

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	glViewport(0, 0, width, height);
}

/*The function returns whether this key is currently being pressed. We’re
creating a processInput function to keep all input code organized*/
void processInput(GLFWwindow* window)
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);
}

//Vertices Coordinates
GLfloat vertices[] =
{ //            COORDNATES                         /       COLORS         //
	-0.5f    , -0.5f * float(sqrt(3)) / 3    , 0.0f,  0.0f, 1.0f, 0.0f ,//Lower Left corner
	 0.5f    , -0.5f * float(sqrt(3)) / 3    , 0.0f,  1.0f, 0.0f, 0.0f , //Lower Rigth corner
	 0.0f    ,  0.5f * float(sqrt(3)) * 2 / 3, 0.0f,  0.0f, 0.0f, 1.0f, //Upper corner
	-0.5f / 2,  0.5f * float(sqrt(3)) / 6    , 0.0f,  0.0f, 0.5f, 0.5f, //Inner Left
	 0.5f / 2,  0.5f * float(sqrt(3)) / 6    , 0.0f,  0.5f, 0.0f, 0.5f, //Inner Rigth
	 0.0f    , -0.5f * float(sqrt(3)) / 3    , 0.0f,  0.5f, 0.5f, 0.0f , //Inner down
};

// Indices for vertices order
GLuint indices[] =
{
	0, 3, 5,
	3, 2, 4,
	5, 4, 1
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

	// Links VBO to VAO
	VAO1.linkVBO(VBO1, 0, 3, GL_FLOAT, 6 * sizeof(float), (void*)0);
	VAO1.linkVBO(VBO1, 1, 3, GL_FLOAT, 6 * sizeof(float), (void*)(3*sizeof(float)));
	// Unbind ALL to prevent accidentaly modifying them
	VAO1.Unbind();
	VBO1.Unbind();
	EBO1.Unbind();

	//------------ VERTEX SHADERS CODE FINAL------------------------//

	glClearColor(0.2f, 0.3f, 0.3f, 1.0f);    //Specify color of bg
	glClear(GL_COLOR_BUFFER_BIT);            //Clean back buffer & assign new
	//color to it
	
	//MAin while loop. Window is open until the
	//ESCAPE button is pressed by the user
	while (!glfwWindowShouldClose(window))
	{
		processInput(window); //process if the user has pressed ESCAPE button

		//RENDERING------------------------------------------------------------//
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);    //Specify color of bg
		glClear(GL_COLOR_BUFFER_BIT);            //Clean back buffer & assign new
		                                         //color to it

		// Tell OpenGL which Shader program we want to use
		shaderProgram.Activate();
		// Bind the VAO so OpenGL knows how to use it
		VAO1.Bind();
		// Draw the triangle using the GL_TRIANGLES primitive
		glDrawElements(GL_TRIANGLES, 9, GL_UNSIGNED_INT, 0);

		/*glDrawArrays(GL_TRIANGLES, 0, 3);*/    //This is a for vertex shaders code

		//RENDERING END ------------------------------------------------------//

		//Check and call events and swap buffers
		glfwSwapBuffers(window);
		glfwPollEvents();
	};

	//------------------------ END OF THE PROGRAM B4 EXITING ---------------//

	//Deleting Vertex Shaders
	VAO1.Delete();
	VBO1.Delete();
	EBO1.Delete();
	shaderProgram.Delete();

	//Delete window before exiting the program
	glfwDestroyWindow(window);
	glfwTerminate();

	return 0;
}