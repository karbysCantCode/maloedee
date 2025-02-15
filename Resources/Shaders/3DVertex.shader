#version 450

layout(std430, binding = 0) buffer SSBO 
{
    vec3 modelPositions[];
};

layout(location = 0) in vec3 position;
layout(location = 1) in vec4 color;
layout(location = 2) in unsigned int modelID;

out vec4 fragColor;

uniform mat4 u_Projection;
uniform mat4 u_View;

void main()
{
	mat4 modelTranslation = mat4(1.0);
	modelTranslation[3] = vec4(modelPositions[modelID], 1.0);
	gl_Position =  u_Projection * u_View * modelTranslation * vec4(position,1.0);
	fragColor = color;
};