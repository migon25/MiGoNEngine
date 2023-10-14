#version 330 core

out vec4 FragColor;

// Color of the light
uniform vec4 lightColor;

// intensity of the light
uniform float intensity;

void main()
{
	FragColor =  lightColor * intensity;
}