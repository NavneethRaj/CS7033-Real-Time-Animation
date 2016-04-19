#version 330 core


in vec3 Reflection;
in vec3 Refraction;
in float fresnel;

uniform samplerCube cubeMap;

out vec4 color;

 void main(void)
 {
    vec4 refractionColor = texture( cubeMap, normalize( Refraction ) );
    vec4 reflectionColor = texture( cubeMap, normalize( Reflection ) );

	color = mix( refractionColor, reflectionColor, fresnel );
	color = mix(color, vec4(0.0,0.3,0.5,1.0), 0.2);
}