#version 330 core

in vec3 transformedNormal;
in vec3 transformedPosition;


uniform samplerCube cubeMap;

out vec4 out_color;

uniform vec3 light_position;
uniform vec3 eye_position;
uniform int material_shininess;
uniform float material_kd;
uniform float material_ks;

const vec3 ambinet = vec3(0.90,0.0,0.20);
//const vec3 Kd = vec3(0.30,0.80,0.10);


const int levels = 5;
const float scaleFactor = 1.0 / levels;

void main(void)
{
    //vec3 reflectedDirection = -normalize(reflect(-EyeDir, transformedNormal));
    //color = texture(cubeMap, reflectedDirection);
    //color = fragColor;
	//color = vec4(1.0f,0,0,1.0f);
	//color = vec4(reflectedDirection.p, 1.0f);
	//color = vec4(transformedNormal.p, 1.0f);
	//color = gl_FragCoord * 0.01f;

	vec3 color= vec3(0.90,0.0,0.20);

	vec3 Kd = vec3(0.30,0.80,0.10);
	
	vec3 L = normalize( light_position - transformedPosition);
	vec3 V = normalize( eye_position - transformedPosition);

	float difuza = max(0, dot(L,transformedNormal));
	Kd = Kd * material_kd* floor(difuza * levels) * scaleFactor;

	vec3 H = normalize(L + V);

	float speculara = 0;

	if( dot(L,transformedNormal) > 0.0)
	{
         speculara = material_ks * pow( max(0, dot( H, transformedNormal)), material_shininess);
		 
	}	
	
	float specMask = (pow(dot(H, transformedNormal), material_shininess) > 0.4) ? 1 : 0;
	float edgeMask = (dot(V, transformedNormal) >  0.2) ? 1 : 0;
	
	color = edgeMask * (color + Kd + speculara * specMask);

	out_color = vec4(color,1);
	
}