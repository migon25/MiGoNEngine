#version 330 core

out vec4 FragColor;

// Color of the light
uniform vec4 lightColor;

void main()
{
	FragColor = lightColor;
}