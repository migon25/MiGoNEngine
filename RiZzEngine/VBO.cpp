#include "VBO.h"

VBO::VBO(std::vector<Vertex>& vertices)
{
	glGenBuffers(1, &ID);
	glBindBuffer(GL_ARRAY_BUFFER, ID);
	glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Vertex), vertices.data(), GL_STATIC_DRAW);
}

void VBO::Bind()
{
	// Bind the VBO specifying it is a GL_ARRAY_BUFFER
	glBindBuffer(GL_ARRAY_BUFFER, ID);
}

void VBO::Unbind()
{
	//unbind VBO by binding it to 0 so we
	//don't accidentaly change it with a function
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void VBO::Delete()
{
	//Deleting Vertex Buffer Shaders
	glDeleteBuffers(1, &ID);
}