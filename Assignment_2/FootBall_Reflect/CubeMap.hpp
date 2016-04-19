#pragma once

#include <IL\il.h>
#include <sstream>
#include <iostream>
#include <Windows.h>
#include <GL\glew.h>
#include <GL\GL.h>
#include <vector>
#include <glm/glm.hpp>
#include <glm\vec3.hpp>
#include <glm\mat4x4.hpp>
#include <glm\gtc\matrix_transform.hpp>

#include "ShaderManager.hpp"


class CubeMap{
private:
	GLuint texID;
	GLuint vbo;
	GLuint vao;
	Shader* _shader;
	//static ILuint* imageIDs;
	//static GLuint* textureIDs;
	void create_cube_map (
	const char* front,
	const char* back,
	const char* top,
	const char* bottom,
	const char* left,
	const char* right,
	GLuint* tex_cube);


	bool CubeMap::load_cube_map_side (GLuint texture, GLenum side_target, const char* file_name);

public:
	CubeMap();

	void loadCubeMap(const char* mapFolder);
	void drawSkyBox();
	void use();

	void setShader(Shader* s);
	void setShader(std::string shader);
	Shader* getShader();

};
