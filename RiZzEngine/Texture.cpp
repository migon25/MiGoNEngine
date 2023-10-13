#include "Texture.h"

Texture::Texture(const char* image, GLenum texType, GLenum slot, GLenum format, GLenum pixelType)
{
	// Assigns the texture type
	type = texType;

	// stores the width, height and the number of color channels of the image
	int widthImg, heightImg, numColCh;

	// Flips the image to the right position
	stbi_set_flip_vertically_on_load(true);

	// Reads the image from file and stores it in bytes
	unsigned char* bytes = stbi_load(image, &widthImg, &heightImg, &numColCh, 0);
	
	// Generates openGL texture object
	glGenTextures(1, &ID);
	// Assigns the texture to a texture Unit
	glActiveTexture(slot);
	glBindTexture(texType, ID);

	// Configures the type of algorithm that is used to scale image
	glTexParameteri(texType, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(texType, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

	// Configures the way the texture repeats
	glTexParameteri(texType, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(texType, GL_TEXTURE_WRAP_T, GL_REPEAT);

	// Border color for the GL_CLAMP_TOBORDER
	float borderColor[] = { 1.0f, 1.0f, 0.0f, 1.0f };
	glTexParameterfv(GL_TEXTURE_2D, GL_TEXTURE_BORDER_COLOR, borderColor);

	// Assigns the image to the openGL texture object
	glTexImage2D(texType, 0, GL_RGBA, widthImg, heightImg, 0, format, pixelType, bytes);
	// Generates mipmaps
	glGenerateMipmap(texType);

	// Deletes the image data
	stbi_image_free(bytes);
	// Unbind the OpenGL texture object
	glBindTexture(texType, 0);
}

void Texture::textUnit(Shader& shader, const char* uniform, GLuint unit)
{
	GLuint tex0Uni = glGetUniformLocation(shader.ID, uniform);
	shader.Activate();
	glUniform1i(tex0Uni, unit);
}

void Texture::Bind()
{
	glBindTexture(GL_TEXTURE_2D, ID);
}

void Texture::Unbind()
{
	glBindTexture(GL_TEXTURE_2D, 0);
}

void Texture::Delete()
{
	glDeleteTextures(1, &ID);
}