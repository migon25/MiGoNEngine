#version 330 core

// Coordinates
layout (location = 0) in vec3 aPos;
// Color
layout (location = 1) in vec3 aColor;
// Texture
layout (location = 2) in vec2 aTex;

// Outputs the color
out vec3 color;

// Outputs the texture coordinates for FragShader
out vec2 texCoord;

// Outputs the current position of the Fragment Shader
out vec3 crntPos;

// Controls the scale of the vertices
uniform float scale;

// Imports	the camera matrix from the main function
uniform mat4 camMatrix;

// Imports the model matrix from the main function
uniform mat4 model;

void main()
{
   // Calculates current position
	crntPos = vec3(model * vec4(aPos, 1.0f)) * scale;
   // Outputs the position/coordinates of all vertices
   gl_Position = camMatrix * vec4(crntPos, 1.0);
   
   //Assigns the color from the vertex data to "color"
   color = aColor;

   //Assigns texture coordinates from the vertex data to "texCoord"
   texCoord = aTex;
}