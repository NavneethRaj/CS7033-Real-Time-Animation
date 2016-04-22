#include <stdio.h>		// - Just for some ASCII messages
#include "gl\glut.h"	// - An interface and windows management library
#include "visuals.h"	// Header file for our OpenGL functions

					 
////////////////// State Variables ////////////////////////
float t=0.0; ///Time

/////////////// Main Program ///////////////////////////

int main(int argc, char* argv[])
{ 
  // initialize GLUT library state
  glutInit(&argc, argv);
	
  glutInitDisplayMode(GLUT_RGBA|GLUT_DOUBLE);
 
  glutInitWindowSize(1000,700);
  glutInitWindowPosition(50,50);
  
  // Create and label the main window
  glutCreateWindow("Interactive Application");
  
  // Configure various properties of the OpenGL rendering context
  Setup();
  
  // Callbacks for the GL and GLUT events:

  // The rendering function 
  glutDisplayFunc(Render);
  glutReshapeFunc(Resize);
  glutIdleFunc(Idle);
  glutKeyboardFunc(Keyboard);
  glutSpecialFunc(special);
  glutMouseFunc(Mouse);
  glutMotionFunc(Motion);
 
  //Enter main event handling loop
  glutMainLoop();
  return 0;


}  
