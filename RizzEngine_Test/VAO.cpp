#include "VAO.h"

VAO::VAO()
{
	glGenVertexArrays(1, &ID);
}

void VAO::linkVBO(VBO VBO, GLuint layout, GLuint numComponents, GLenum type, GLsizeiptr stride, void* offset)
{
	VBO.Bind();
	// Tell OpenGL where to find the buffers and how to read the VBO
	glVertexAttribPointer(layout, numComponents, type, GL_FALSE, stride, offset);
	// Enable Vertex Attribute so OpenGL knows how to use it
	glEnableVertexAttribArray(layout);
	VBO.Unbind();
}

void VAO::Bind()
{
	// MAke the VAO the current Vertex Array Object by binding it
	glBindVertexArray(ID);
}

void VAO::Unbind()
{
	//unbind VAO by binding it to 0 so we
	//don't accidentaly change it with a function
	glBindVertexArray(0);
}

void VAO::Delete()
{
	//Deleting Vertex Shaders
	glDeleteVertexArrays(1, &ID);
}