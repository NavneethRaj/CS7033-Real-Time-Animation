#version 330 core

layout (location = 0) in vec3 v_coord;
layout (location = 1) in vec4 v_diffuse;
layout (location = 2) in float point_size;

uniform mat4 m, v, p; 
out vec4 colour;

void main(){
	mat4 VP = p * v;
	gl_Position = VP * vec4(v_coord,1);
	colour = v_diffuse;
	//gl_PointSize = point_size;

	// Calculate the distance to the camera
	vec4 eyePos = v * vec4(v_coord,1);
	float dist = length(vec3(eyePos));
	gl_PointSize = point_size * (8.0 / dist);

}