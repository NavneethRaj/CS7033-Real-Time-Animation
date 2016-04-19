#include <iostream>

#include <GL\glew.h>
#include <GLFW/glfw3.h>

#include "ShaderManager.hpp"
#include "Entity.hpp"
#include "CubeMap.hpp"
#include "glm/gtc/matrix_transform.hpp"

GLFWwindow* window;

glm::mat4 ViewMatrix;
glm::mat4 ProjectionMatrix;

glm::mat4 getViewMatrix(){
	return ViewMatrix;
}
glm::mat4 getProjectionMatrix(){
	return ProjectionMatrix;
}

// Initial position : on +Z
glm::vec3 position = glm::vec3( 0, 0, 5 ); 
// Initial horizontal angle : toward -Z
float horizontalAngle = 3.14f;
// Initial vertical angle : none
float verticalAngle = 0.0f;
// Initial Field of View
float initialFoV = 45.0f;

float speed = 3.0f; // 3 units / second
float mouseSpeed = 0.005f;


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

	window = glfwCreateWindow(800, 800, "Transmittance", NULL, NULL);
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

int main()
{
	/* Create GL Window */
	if (!initWindow())
		return -1;

	/* Initialise vertex buffers for cube */
	CubeMap cubeMap;
	cubeMap.loadCubeMap("../textures/cubemaps/Yokohama/");
	cubeMap.setShader(ShaderManager::loadShader("cube3"));

	/* Load shaders needed */
	

	Entity dragonModel;
	dragonModel.loadFromFile("../models/Drone.dae");
	dragonModel.setShader(ShaderManager::loadShader("fresnel2"));

	glEnable(GL_DEPTH_TEST);
	while (!glfwWindowShouldClose(window))
	{
		/* Rendering Code */
		glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

			// glfwGetTime is called only once, the first time this function is called
	static double lastTime = glfwGetTime();

	// Compute time difference between current and last frame
	double currentTime = glfwGetTime();
	float deltaTime = float(currentTime - lastTime);

	// Get mouse position
	double xpos, ypos;
	glfwGetCursorPos(window, &xpos, &ypos);

	// Reset mouse position for next frame
	glfwSetCursorPos(window, 1024/2, 768/2);

	// Compute new orientation
	horizontalAngle += mouseSpeed * float(1024/2 - xpos );
	verticalAngle   += mouseSpeed * float( 768/2 - ypos );

	// Right vector
	glm::vec3 right = glm::vec3(
		sin(horizontalAngle - 3.14f/2.0f), 
		0,
		cos(horizontalAngle - 3.14f/2.0f)
	);

	glm::vec3 direction(
		cos(verticalAngle) * sin(horizontalAngle), 
		sin(verticalAngle),
		cos(verticalAngle) * cos(horizontalAngle)
	);

	glm::vec3 up = glm::cross( right, direction );

	// Move forward
	if (glfwGetKey( window, GLFW_KEY_UP ) == GLFW_PRESS){
		position += direction * deltaTime * speed;
	}
	// Move backward
	if (glfwGetKey( window, GLFW_KEY_DOWN ) == GLFW_PRESS){
		position -= direction * deltaTime * speed;
	}
	// Strafe right
	if (glfwGetKey( window, GLFW_KEY_RIGHT ) == GLFW_PRESS){
		position += right * deltaTime * speed;
	}
	// Strafe left
	if (glfwGetKey( window, GLFW_KEY_LEFT ) == GLFW_PRESS){
		position -= right * deltaTime * speed;
	}

	float FoV = initialFoV;// - 5 * glfwGetMouseWheel(); // Now GLFW 3 requires setting up a callback for this. It's a bit too complicated for this beginner's tutorial, so it's disabled instead.

	// Projection matrix : 45° Field of View, 4:3 ratio, display range : 0.1 unit <-> 100 units
	ProjectionMatrix = glm::perspective(glm::radians(FoV), 4.0f / 3.0f, 0.1f, 100.0f);
	// Camera matrix
	ViewMatrix       = glm::lookAt(
								position,           // Camera is here
								position+direction, // and looks here : at the same position, plus "direction"
								up                  // Head is up (set to 0,-1,0 to look upside-down)
						   );

	// For the next frame, the "last time" will be "now"
	lastTime = currentTime;

		int state1 = glfwGetKey(window, GLFW_KEY_D);
		int state2 = glfwGetKey(window, GLFW_KEY_A);
		int state3 = glfwGetKey(window, GLFW_KEY_W);
		int state4 = glfwGetKey(window, GLFW_KEY_Q);
		int state5 = glfwGetKey(window, GLFW_KEY_E);
		int state6 = glfwGetKey(window, GLFW_KEY_S);
		int state7 = glfwGetKey(window, GLFW_KEY_UP);

		cubeMap.getShader()->setUniformMatrix4fv("projectionMat", ProjectionMatrix);
		cubeMap.getShader()->setUniformMatrix4fv("viewMat", ViewMatrix);
		cubeMap.use();
		cubeMap.drawSkyBox();

		dragonModel.getShader()->setUniformMatrix4fv("projectionMat", ProjectionMatrix);
		dragonModel.getShader()->setUniformMatrix4fv("viewMat", ViewMatrix);
		dragonModel.getShader()->setUniformVector4fv("camPos", glm::vec4(0.0f, 0.0f, 5.0f, 1.0f));
		
		if (state1 == GLFW_PRESS)
        dragonModel.rotate(glm::vec3(0.0f,0.01f,0.0f));
		else if (state2 == GLFW_PRESS)
		dragonModel.rotate(glm::vec3(0.01f, 0.0f, 0.0f));
		else if (state3 == GLFW_PRESS)
		dragonModel.rotate(glm::vec3(0.0f, 0.0f, 0.01f));
		else if (state4 == GLFW_PRESS)
		dragonModel.rotate(glm::vec3(0.0f, -0.01f, 0.0f));
		else if (state5 == GLFW_PRESS)
		dragonModel.rotate(glm::vec3(-0.01f, 0.0f, 0.0f));
		else if (state6 == GLFW_PRESS)
		dragonModel.rotate(glm::vec3(0.0f, 0.0f, -0.01f));
		
		dragonModel.draw();
		
	    glDisable(GL_TEXTURE_GEN_S);
		glDisable(GL_TEXTURE_GEN_T);
		glDisable(GL_TEXTURE_GEN_R);
		glEnable(GL_TEXTURE_GEN_S);
		glEnable(GL_TEXTURE_GEN_T);
		glEnable(GL_TEXTURE_GEN_R);

		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	glfwTerminate();
	return 0;
}
