#version 330 core

// Coordinates
layout (location = 0) in vec3 aPos;
// Normal
layout (location = 1) in vec3 aNormal;
// Color
layout (location = 2) in vec3 aColor;
// Texture
layout (location = 3) in vec2 aTex;

// Outputs the current position of the Fragment Shader
out vec3 crntPos;
// Outputs normals to the FragShader
out vec3 Normal;
// Outputs the color
out vec3 color;
// Outputs the texture coordinates for FragShader
out vec2 texCoord;

// Imports	the camera matrix from the main function
uniform mat4 camMatrix;
// Imports the model matrix from the main function
uniform mat4 model;
uniform mat4 translation;
uniform mat4 translationMatrix;
uniform mat4 rotation;
uniform mat4 rotationMatrix;
uniform mat4 scale;
uniform float scaleX;
uniform float scaleY;
uniform float scaleZ;
uniform float imguiScale;

void main()
{
   // Calculates current position, used to calculate the direction of light
	crntPos = vec3(model * translation * translationMatrix * rotationMatrix * -rotation * vec4(aPos.x * scaleX, aPos.y * scaleY, aPos.z * scaleZ, 1.0)) * imguiScale;
   //Normal matrix fpr the pyramid
   Normal = aNormal;
   //Assigns the color from the vertex data to "color"
   color = aColor;
   //Assigns texture coordinates from the vertex data to "texCoord"
	texCoord = mat2(0.0, -1.0, 1.0, 0.0) * aTex;

   // Outputs the position/coordinates of all vertices
   gl_Position = camMatrix * vec4(crntPos, 1.0);
}