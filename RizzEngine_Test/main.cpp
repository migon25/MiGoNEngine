#include <stdlib.h>
#include <stdio.h>
#include <iostream>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "shaderClass.h"

#define WINDOW_WIDTH  800
#define WINDOW_HEIGHT 600
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


int main() {

	//initializing GLFW
	glfwInit();

	//Tell GLFW what version of OpenGL we are using
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	//Tell GLFW that we are using CORE profile
	//so that means we only have the modern
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

	//Vertices Coordinates
	GLfloat vertices[] =
	{
		-0.5f, -0.5f * float(sqrt(3)) / 3    , 0.0f, //Lower Left corner
		 0.5f, -0.5f * float(sqrt(3)) / 3    , 0.0f, //Lower Rigth corner
		 0.0f,  0.5f * float(sqrt(3)) * 2 / 3, 0.0f, //Upper corner
	};

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

	// Specify the viewport of OpenGL in the window
	// from x = 0, y = 0, to x = WINDW_WIDTH, y = WINDOW_HEIGHT
	glViewport(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT);


	//------------ VERTEX SHADERS CODE FINAL------------------------//

	// Create Vertex Shader Object and get reference
	GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
	// Attach Vertex shader source to the Vertex Shader Object
	glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
	// Compile the Vertex shader into machine code
	glCompileShader(vertexShader);

	// Create Fragment Shader Object and get reference
	GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	// Attach Fragment shader source to the Fragment Shader Object
	glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
	// Compile the Fragment shader into machine code
	glCompileShader(fragmentShader);

	// Create Shader Program Object and get its reference
	GLuint shaderProgram = glCreateProgram();
	// Attach Vertex and Fragment shader to the Shader Program
	glAttachShader(shaderProgram, vertexShader);
	glAttachShader(shaderProgram, fragmentShader);
	// Wrap-up/link all the shaders together into the shader program
	glLinkProgram(shaderProgram);

	// Delete teh useless Vertex and fragment shader objects
	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);


	// Create reference containers for the Vertex Array Object and the Vertex Buffer Object
	GLuint VAO, VBO;

	// Generate VAO and VBO with only 1 object each
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);

	// MAke the VAO the current Vertex Array Object by binding it
	glBindVertexArray(VAO);

	// Bind the VBO specifying it is a GL_ARRAY_BUFFER
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	// Store vertices in the buffer VBO
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	// Tell OpenGL where to find the buffers and how to read the VBO
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	// Enable Vertex Attribute so OpenGL knows how to use it
	glEnableVertexAttribArray(0);

	//unbind VBO and VAO by binding it to 0 so we
	//don't accidentaly change it with a function
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);

	//------------ VERTEX SHADERS CODE FINAL------------------------//

	// ---------------------------VERTEX SHADERS CODE---------------------------//
	//glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

	////Vertices of our triangle
	//float vertices[9] = {
	//	-0.5f, -0.5f, 0.0f,
	//	 0.5f, -0.5f, 0.0f,
	//	 0.0f,  0.5f, 0.0f
	//};

	////creating/assigning a buffer
	//unsigned int VertexBufferObject;
	//glGenBuffers(1, &VertexBufferObject);
	//glBindBuffer(GL_ARRAY_BUFFER, VertexBufferObject);
	//glBufferData(GL_ARRAY_BUFFER, 9*sizeof(float), vertices, GL_STATIC_DRAW);

	//glBindBuffer(GL_ARRAY_BUFFER, 0);
	// -----------------------VERTEX SHADERS CODE END---------------------------//

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
		glUseProgram(shaderProgram);
		// Bind the VAO so OpenGL knows how to use it
		glBindVertexArray(VAO);
		// Draw the triangle using the GL_TRIANGLES primitive
		glDrawArrays(GL_TRIANGLES, 0, 3);

		/*glDrawArrays(GL_TRIANGLES, 0, 3);*/    //This is a for vertex shaders code

		//RENDERING END ------------------------------------------------------//

		//Check and call events and swap buffers
		glfwSwapBuffers(window);
		glfwPollEvents();
	};

	//------------------------ END OF THE PROGRAM B4 EXITING ---------------//

	//Deleting Vertex Shaders
	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);
	glDeleteProgram(shaderProgram);

	//Delete window before exiting the program
	glfwDestroyWindow(window);
	glfwTerminate();

	return 0;
}