#version 330 core

const float Glass = 1.51714; 
const float Air = 1.0;
const float Eta = Air / Glass; // Ratio of indices of refraction
const float R0 = ((Air - Glass) * (Air - Glass)) / ((Air + Glass) * (Air + Glass));   //Reflectivity

in vec3 a_vertex;
in vec3 a_normal;
//in vec3 camPos;

out vec3 Reflection;
out vec3 Refraction;
out float fresnel;

uniform mat4 modelMat;
uniform mat4 viewMat;
uniform mat4 projectionMat;
uniform mat3 normalMat;
uniform vec3 camPos;

void main()
{
	vec4 vertex = modelMat * vec4(a_vertex,1.0);
	vec4 camera = vec4(camPos,1.0);
	
	vec3 incident = normalize(vec3(vertex-camera));
	
	vec3 normal = normalMat * a_normal;
	
	Refraction = refract(incident, normal, Eta);
	Reflection = reflect(incident, normal);
	
	fresnel = R0 + (1.0 - R0) * pow( (1.0 - dot( -incident, normal ) ), 5.0);
	
	mat4 MVP = projectionMat * viewMat;
	
	gl_Position = MVP * vertex;

}