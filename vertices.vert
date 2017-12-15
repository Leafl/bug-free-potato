#version 330 core

layout(location = 0) in vec3 VertexPosition;
layout(location = 1) in vec3 VertexColor;
layout(location = 2) in vec3 VertexNormal;

uniform mat4 PVMMatrix;
uniform mat3 NormalMatrix; 	// to transform normals, pre-perspective
uniform vec3 EyePosition;
uniform vec3 LightDirection;

out vec3 Color;
out vec3 Normal;
out vec3 HalfVector;

void main()
{
	Color = VertexColor;
	Normal = normalize(NormalMatrix * VertexNormal);

	vec3 EyeDirection = normalize(VertexPosition - EyePosition);
	HalfVector = normalize(LightDirection + EyeDirection);

	gl_Position = PVMMatrix * vec4(VertexPosition, 1.0);
}
