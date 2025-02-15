#version 450 core

layout(std430, binding = 0) buffer SSBO 
{
    float modelData[];
};

layout(location = 0) in vec3 position;
layout(location = 1) in uint modelID;

out vec4 fragColor;

uniform mat4 u_Projection;
uniform mat4 u_View;

void main()
{
    const unsigned int modelIndex = 7 * modelID; // NUMBER OF FLOATS IN MODEL DATA ENTRY
	mat4 modelTranslation = mat4(
    vec4(1.0, 0.0, 0.0, 0.0),
    vec4(0.0, 1.0, 0.0, 0.0),
    vec4(0.0, 0.0, 1.0, 0.0),
    vec4(modelData[modelIndex],modelData[modelIndex+1],modelData[modelIndex+2],1.0f)
    );

	gl_Position =  u_Projection * u_View * modelTranslation * vec4(position,1.0);
	fragColor = vec4(modelData[modelIndex+3],modelData[modelIndex+4],modelData[modelIndex+5],modelData[modelIndex+6]);
};