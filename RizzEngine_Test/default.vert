#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aColor;
layout (location = 2) in vec2 aTex;

// Outputs the color
out vec3 color;

// Outputs the texture coordinates
out vec2 texCoord;

// Controls the scale of the vertices
uniform float scale;

void main()
{
   gl_Position = vec4(aPos.x + aPos.x * scale, aPos.y + aPos.y * scale, aPos.z + aPos.z * scale, 1.0);
   //Assigns the color from the vertex data to "color"
   color = aColor;
   texCoord = aTex;
}