#include <iostream>

#include <GL\glew.h>
#include <GLFW/glfw3.h>

#include "ShaderManager.hpp"
#include "Entity.hpp"
#include "CubeMap.hpp"

GLFWwindow* window;
#define window_width 1024
#define window_height 980
 
float a = 0.0f;
// position
glm::vec3 Camposition = glm::vec3( 0.0f, 5.0f, 5.0f );
glm::vec3 direction = glm::vec3( 0.0f, 0.0f, -1.0f );
glm::vec3 up = glm::vec3( 0.0f, 1.0f, 0.0f );
glm::vec3 rightv = glm::vec3( 0.0f, 0.0f, 0.0f );

// horizontal angle : toward -Z
float horizontalAngle = 3.14f;
// vertical angle : 0, look at the horizon
float verticalAngle = 0.0f;
// Initial Field of View
float FoV = 45.0F;

float speed = 4.0f; // 3 units / second
float mouseSpeed = 0.005f;
bool keys[1024];
float lastTime;
float deltaTime;
//cursor para
bool mouse[20] = {false};
bool firstPush = true;
float preRotX,preRotY,RotX,RotY;
float rotateSpeed = 0.01;

//parameter for shaders
bool bump = false;
float swich =1.0f;

bool initWindow()
{
	if (!glfwInit())
	{
		std::cout << "ERROR: Could not initialise GLFW...";
		std::cin;
		return false;
	}

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	window = glfwCreateWindow(800, 800, "Catch The Models", NULL, NULL);
	if (!window)
	{
		glfwTerminate();
		std::cout << "ERROR: Could not create winodw...";
		std::cin;
		return false;
	}

	glfwMakeContextCurrent(window);

	std::cout << "OpenGL version: " << glGetString(GL_VERSION) << std::endl;

	glewExperimental = GL_TRUE;
	GLenum err = glewInit();

	if (err != GLEW_OK)
	{
		std::cout << "ERROR: Problem initialising GLEW: " << glewGetErrorString(err);
		std::cin;
		return false;
	}

	glViewport(0, 0, 800, 800);

	return true;
}

//Camera caculation
void computeMatricesFromInputs()
	{
	double xpos, ypos;
	glfwGetCursorPos(window, &xpos, &ypos);
	// Compute new orientation
	horizontalAngle += mouseSpeed * deltaTime * float(window_width/2 - xpos );
	verticalAngle   += mouseSpeed * deltaTime * float( window_height/2 - ypos );
	// Direction : Spherical coordinates to Cartesian coordinates conversion
	direction = glm::vec3 (
    cos(verticalAngle) * sin(horizontalAngle),
    sin(verticalAngle),
    cos(verticalAngle) * cos(horizontalAngle)
	);
	// Right vector

	rightv = glm::normalize(glm::vec3(glm::cross(direction,glm::vec3(0.0,1.0,0.0))));
	// Up vector : perpendicular to both direction and right
	up = glm::cross( rightv, direction );

	}
glm::mat4 getViewMatrix()
{
	// Camera matrix
	glm::mat4 ViewMatrix = glm::lookAt(
    Camposition,           // Camera is here
    Camposition+direction, // and looks here : at the same position, plus "direction"
    up                  // Head is up (set to 0,-1,0 to look upside-down)
	);
	return ViewMatrix;
}
glm::mat4 getProjectionMatrix()
{ 
	 glm::mat4 projectionMatrix = glm::perspective(FoV, float(window_width)/float(window_height), 1.0f, 1000.0f);
	 return projectionMatrix;
}
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{
	if(FoV>=1.0f && FoV<=45.0f)
	{
	FoV -= 0.1f* yoffset;
	}
	if (FoV<1.0f)
	{
		FoV=1.0f;
	}
	if (FoV>45.0f)
	{
		FoV = 45.0f;
	}
	std::cout<<"yoffset "<<yoffset<<std::endl;
	std::cout<<"Fov IS "<<FoV<<std::endl;
} 
void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	if(key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
        glfwSetWindowShouldClose(window, GL_TRUE);

    if(action == GLFW_PRESS)
        keys[key] = true;
    else if(action == GLFW_RELEASE)
        keys[key] = false;

}
void mousebutton_callback(GLFWwindow* window, int button, int action, int mods)
{
	if(action == GLFW_PRESS)
		mouse[button] = true;
	else if (action == GLFW_RELEASE)
		mouse[button] = false;

}
// Input action
void KeyAction()
{
		if( keys[GLFW_KEY_W])
	{
		 Camposition += direction * deltaTime * speed;
	}
	if( keys[GLFW_KEY_S])
	{
		 Camposition -= direction * deltaTime * speed;
	}
	if( keys[ GLFW_KEY_D])
	{
		Camposition += rightv * deltaTime * speed;
	}
	if(   keys[ GLFW_KEY_A] )
	{
		 Camposition -= rightv * deltaTime * speed;
	}
	if( keys[ GLFW_KEY_UP] )
	{
			speed++;
	}
	if( keys[ GLFW_KEY_DOWN] )
	{
			speed--;
	}

	//key behavior for bump-map
	if(keys[GLFW_KEY_N])
	{
		bump = 1.0 ;
	}
	
	if (keys[GLFW_KEY_M])
	{
		bump = 0.0;
	}
	
	//key behavior for reflection
	if (keys[GLFW_KEY_1])//reflection
	{
		swich = 1.0;
	}
	if (keys[GLFW_KEY_2])//refraction
	{
		swich = 2.0;
	}
	if (keys[GLFW_KEY_3])//combine
	{
		swich = 3.0;
	}
}
void MouseAction()
{
	if (mouse[GLFW_MOUSE_BUTTON_LEFT])
	{
		double xpos = 0 , ypos= 0 ;
		float Ori_rotateX = 0.0, Ori_rotateY = 0.0;
		glfwGetCursorPos(window, &xpos, &ypos);
		if (firstPush)//the first push
		{
			firstPush = false;
			Ori_rotateX = xpos;
			Ori_rotateY = ypos;
			//std::cout<<"X: "<<xpos<<" , "<<"Y: "<<ypos<<std::endl;
		}
		else//listen course position when pushing
		{
			RotX = (xpos - Ori_rotateX) * rotateSpeed;
			RotY = (ypos - Ori_rotateY) * rotateSpeed;
			//std::cout<<"RotX: "<<RotX<<" , "<<"RotY: "<<RotY<<std::endl;
		}
	}
	else if (!mouse[GLFW_MOUSE_BUTTON_LEFT])
	{
		firstPush = true;
		preRotX += RotX;
		preRotY += RotY;
		RotX = 0;
		RotY = 0;
	}
}


int main()
{
	/* Create GL Window */
	if (!initWindow())
		return -1;

	glEnable(GL_BLEND);// you enable blending function
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA); 

	glfwSetScrollCallback(window,scroll_callback);
	glfwSetKeyCallback(window,key_callback);
	glfwSetMouseButtonCallback(window,mousebutton_callback);

	/* Initialise vertex buffers for cube */
	CubeMap cubeMap;
	cubeMap.loadCubeMap("../textures/cubemaps/Yokohama/");
	cubeMap.setShader(ShaderManager::loadShader("cube3"));

	/* Load shaders needed */
	

	Entity dragonModel;
	dragonModel.loadFromFile("../models/Drone.dae");
	dragonModel.setShader(ShaderManager::loadShader("toon3"));


  
	glEnable(GL_DEPTH_TEST);
	while (!glfwWindowShouldClose(window))
	{
		/* Rendering Code */
		glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		double currentTime = glfwGetTime();
		deltaTime = float(currentTime - lastTime);
		lastTime = currentTime;

		//Compute the MV matrix from the keyboard and mouse
		KeyAction();
		MouseAction();
		if (!mouse[GLFW_MOUSE_BUTTON_LEFT])//when dragging, fix the camera
		{
			computeMatricesFromInputs();
		}

		glm::mat4 projectionMatrix = getProjectionMatrix();
		glm::mat4 ViewMatrix = getViewMatrix();

		GLfloat near_plane =1.0f, far_plane = 7.5f;
		glm::mat4 lightProjection = glm::ortho(-10.0f, 10.0f,-10.0f,10.0f,near_plane,far_plane);
		glm::mat4 lightView = glm::lookAt(glm::vec3(0.0f,0.0f,4.0f), glm::vec3(0.0f,0.0f,0.0f), glm::vec3(0.0f,1.0f,0.0f)); 
		glm::mat4 lightSpaceMatrix = lightProjection * lightView;

		int state1 = glfwGetKey(window, GLFW_KEY_D);
		int state2 = glfwGetKey(window, GLFW_KEY_A);
		int state3 = glfwGetKey(window, GLFW_KEY_W);
		int state4 = glfwGetKey(window, GLFW_KEY_Q);
		int state5 = glfwGetKey(window, GLFW_KEY_E);
		int state6 = glfwGetKey(window, GLFW_KEY_S);
		int state7 = glfwGetKey(window, GLFW_KEY_UP);

		cubeMap.getShader()->setUniformMatrix4fv("projectionMat", projectionMatrix);
		cubeMap.getShader()->setUniformMatrix4fv("viewMat", ViewMatrix);
		//cubeMap.use();
		//cubeMap.drawSkyBox();

		dragonModel.getShader()->setUniformMatrix4fv("projectionMat", projectionMatrix);
		dragonModel.getShader()->setUniformMatrix4fv("viewMat", ViewMatrix);
		dragonModel.getShader()->setUniformVector4fv("camPos", glm::vec4(0.0f, 5.0f, 0.0f, 1.0f));
		//dragonModel.rotate(glm::vec3(0.0f, 0.0001f, 0.0f));
		if (state1 == GLFW_PRESS)
        dragonModel.rotate(glm::vec3(0.0f, 0.001f, 0.0f));
		else if (state2 == GLFW_PRESS)
		dragonModel.rotate(glm::vec3(0.001f, 0.0f, 0.0f));
		else if (state3 == GLFW_PRESS)
		dragonModel.rotate(glm::vec3(0.0f, 0.0f, 0.001f));
		else if (state4 == GLFW_PRESS)
		dragonModel.rotate(glm::vec3(0.0f, -0.001f, 0.0f));
		else if (state5 == GLFW_PRESS)
		dragonModel.rotate(glm::vec3(-0.001f, 0.0f, 0.0f));
		else if (state6 == GLFW_PRESS)
		dragonModel.rotate(glm::vec3(0.0f, 0.0f, -0.001f));
		dragonModel.draw();

	    glDisable(GL_TEXTURE_GEN_S);
		glDisable(GL_TEXTURE_GEN_T);
		glDisable(GL_TEXTURE_GEN_R);
		//CubeMap::drawSkyBox();
		glEnable(GL_TEXTURE_GEN_S);
		glEnable(GL_TEXTURE_GEN_T);
		glEnable(GL_TEXTURE_GEN_R);

		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	glfwTerminate();
	return 0;
}
