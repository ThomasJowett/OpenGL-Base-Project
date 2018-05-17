#version 460

layout(location = 0) in vec3 position;
layout(location = 1) in vec2 texCoord;
layout(location = 2) in vec3 normal;

out VertexData {
	vec3 posW;
	vec2 texCoord;
	vec3 normal;
	vec3 eye;
	vec3 lightDir;
} VertexOut;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;
uniform vec3 eyePosW;
uniform vec4 lightPosW;

buffer

void main()
{
	vec4 posW = model * vec4(position,1.0);
	VertexOut.posW = posW.xyz;
	gl_Position = projection * view * posW;

	VertexOut.normal = normalize((model * vec4(normal, 0.0)).xyz);

	VertexOut.texCoord = texCoord;

	VertexOut.eye = eyePosW;

	VertexOut.lightDir = vec3(lightPosW - posW);
}
