#version 330 core
in vec3 position;

uniform mat4 modelMat;
uniform mat4 viewMat;
uniform mat4 projectionMat;
uniform mat4 translateMat;

void main()
{
	mat4 MVP = projectionMat * viewMat * translateMat * modelMat;
	gl_Position = MVP * vec4(position.x, position.y, position.z, 1.0);
}