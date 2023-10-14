#version 330 core

// Outputs colors in RGBA
out vec4 FragColor;


// inputs the color from the vertex shader
in vec3 color;
// inputs the texture coordinates from the vertex shader
in vec2 texCoord;
// Imports the normal from the Vertex Shader
in vec3 Normal;
// Imports the current position from the Vertex Shader
in vec3 crntPos;

// Gets the Texture Unit from the main function
uniform sampler2D tex0;
uniform sampler2D tex1;

// Gets the position of the light from the main function
uniform vec3 lightPos;
// Gets the color of the light from the main function
uniform vec4 lightColor;
// Gets the position of the camera from the main function for specular lighting
uniform vec3 camPos;

//imgui window color test
uniform vec4 ImGuiColor;
//Texture resize
uniform float TexSize;
//Light intensity
uniform float intensity;

vec4 poinLight()
{
    vec3 lightVec = lightPos - crntPos;
    float dist = length(lightVec);
    float a = 1.0f;
    float b = 0.7f;
    float inten = 1.0f /(a * dist * dist + b * dist + 1.0f);


    //ambient light
    float ambient = 0.2f;

    //diffuse light
    vec3 normal = normalize(Normal);
    vec3 lightDirection = normalize(lightVec);
    float diffuse = max(dot(normal, lightDirection), 0.0f);

    //specular light
    float specularLight = 0.5f;
    vec3 viewDirection = normalize(camPos - crntPos);
    vec3 reflectionDirection = reflect(-lightDirection, normal);
    float specAmount = pow(max(dot(viewDirection, reflectionDirection), 0.0f), 16);
    float specular = specAmount * specularLight;

    vec2 texResized = texCoord * TexSize;
    return ((texture(tex0, texResized) * (diffuse * inten + ambient) + texture(tex1, texResized).r * specular * inten) * vec4(ImGuiColor+lightColor)) * intensity;
}

vec4 directLight()
{
    //ambient light
    float ambient = 0.2f;

    //diffuse light
    vec3 normal = normalize(Normal);
    vec3 lightDirection = normalize(vec3(1.0f, 1.0f, 0.0f));
    float diffuse = max(dot(normal, lightDirection), 0.0f);

    //specular light
    float specularLight = 0.5f;
    vec3 viewDirection = normalize(camPos - crntPos);
    vec3 reflectionDirection = reflect(-lightDirection, normal);
    float specAmount = pow(max(dot(viewDirection, reflectionDirection), 0.0f), 16);
    float specular = specAmount * specularLight;

    vec2 texResized = texCoord * TexSize;
    return ((texture(tex0, texResized) * (diffuse+ ambient) + texture(tex1, texResized).r * specular) * vec4(ImGuiColor+lightColor)) * intensity;
}

vec4 spotLight()
{
    float innerCone = 0.95f;
    float outerCone = 0.80f;

   //ambient light
    float ambient = 0.2f;

	// diffuse lighting
	vec3 normal = normalize(Normal);
	vec3 lightDirection = normalize(lightPos - crntPos);
	float diffuse = max(dot(normal, lightDirection), 0.0f);

	// specular lighting
	float specularLight = 0.50f;
	vec3 viewDirection = normalize(camPos - crntPos);
	vec3 reflectionDirection = reflect(-lightDirection, normal);
	float specAmount = pow(max(dot(viewDirection, reflectionDirection), 0.0f), 16);
	float specular = specAmount * specularLight;
	
    // calculates the intensity of the crntPos based on its angle to the center of the light cone
	float angle = dot(vec3(0.0f, -1.0f, 0.0f), -lightDirection);
	float inten = clamp((angle - outerCone) / (innerCone - outerCone), 0.0f, 1.0f);

    vec2 texResized = texCoord * TexSize;
    return ((texture(tex0, texResized) * (diffuse * inten + ambient) + texture(tex1, texResized).r * specular * inten) * vec4(ImGuiColor+lightColor)) * intensity;
}

void main()
{
    // outputs final color;
    FragColor = spotLight();
}