#version 330 core
out vec4 FragColor;

// inputs the color from the vertex shader
in vec3 color;

void main()
{
    FragColor = texture(tex0, texCoord)*vec4(color,1.0);
}