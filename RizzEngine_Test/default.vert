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

// Controls the scale of the vertices
uniform float scale;

void main()
{
   gl_Position = vec4(aPos.x + aPos.x * scale, aPos.y + aPos.y * scale, aPos.z + aPos.z * scale, 1.0);
   //Assigns the color from the vertex data to "color"
   color = aColor;

   //Assigns texture coordinates from the vertex data to "texCoord"
   texCoord = aTex;
}