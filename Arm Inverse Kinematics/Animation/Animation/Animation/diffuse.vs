#version 330

in vec4 vPosition;
in vec4 vColor;
out vec4 color;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

void main()
{
	gl_Position = projection * view * model * vec4(vPosition.x, vPosition.y, vPosition.z, 1.0);
	color = vColor;
}