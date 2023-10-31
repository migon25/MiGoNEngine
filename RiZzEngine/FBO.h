#ifndef FBO_CLASS_H
#define FBO_CLASS_H

#include <iostream>
#include <glad/glad.h>
#include <glm/glm.hpp>

class FBO
{
public:
	FBO(float width, float height);
	~FBO();

	unsigned int getFrameTexture();
	void RescaleFBO(float width, float hwight);
	void Bind() const;
	void Unbind() const;

private:
	GLuint ID;
	GLuint texture;
	GLuint rbo;

};

#endif