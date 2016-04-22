#include <stdio.h>		// - Just for some ASCII messages
#include <stdlib.h>
#include <string.h>
#include <math.h>	
#include <iostream>
#include <fstream>
#include <Windows.h>
#include <time.h>	

#include "gl/glut.h"	// - An interface and windows management library
#include "visuals.h"	// - Header file for our OpenGL functions

using namespace std;

#include "ik/irrKlang.h"		//for sound effect

#pragma comment(lib, "irrKlang.lib") // link with irrKlang.dll

using namespace irrklang;		//for sound effect

bool car_mode = false;	

model md;			//for the trees
model car;
model grass;
bool grass_mode = true;
float LegMovement=35.0f;
float LegMovement2=-50.0f;
float LegSpeed = 1.0f;
float Tilted_front = 4.0f;
float car_passing = 550.0f;
float Item_passing = 550.0f;
float Tree_passing[5]={-400,-100,200,500,800};
float fliping=0.0f;
bool R_x = false;
bool R_y = false;
float Rotate_in_x = 0;
float Rotate_in_y = 0;
float TranslateY=0.0f;
float v=40.0;
bool jump = false;
bool negative = false;
bool first = false;
bool mouse_vision_y = false;
bool mouse_vision_x = false;
bool Enable_flip = false;
bool flip = false;
float forhelp = 0.0f;
bool eleos = false;
bool message = false;
bool message_car = false;
bool pagwse = false;
float zoom  =-300;
static bool pause = false;
float global_w=-1;
float global_h;
bool for_color_pause=false;
ISoundEngine* engine = createIrrKlangDevice();
/*************************************************************/
/***         MY CHARACTER CREATION                         ***/
/*************************************************************/
void create_character(float leg1_move,float leg2_move,float tilte,float hand1_move,float hand2_move){
	glPushMatrix();	
	
	
	glTranslatef(0,TranslateY,0);
	glRotatef(fliping,1,0,0);
	//---------------------------
	glPushMatrix();				
	glTranslatef(0,-31.2,0);		
	glRotatef(tilte,1,0,0);
	glTranslatef(0,31.2,0);
	///////////////////////////////////////////////////////////////
	//	Hat
	///////////////////////////////////////////////////////////////
	glPushMatrix();
	glColor3f(255.0/255, 255.0/255, 255.0/255);
	glTranslatef(0,88,0);
	glutSolidSphere(3,70,70);
	glPopMatrix(); 

	glPushMatrix();

	glTranslatef(0,3,0);
	glPushMatrix();
	glTranslatef(0,27,0);
	glColor3f(139.0/255,35.0/255,35.0/255);
	glTranslatef(0,32,0);
	glScalef(1,1.3,1);
	glRotatef(-90,1,0,0);
	glutSolidCone(10,20,60,60);
	glPopMatrix(); 
	///////////////////////////////////////////////////////////////
	//	Head
	///////////////////////////////////////////////////////////////
	glPushMatrix();
	glTranslatef(0,28,0);
	glColor3f(255.0/255,140.0/255,105.0/255);
	//glColor3f(130.0/255, 130.0/255, 130.0/255);
	glTranslatef(0,20,0);
	glScalef(1,1.5,1);
	glutSolidSphere(13,70,70);
	glPopMatrix(); 
	//smile
	glPushMatrix();
	glColor3f(0.0/255, 0.0/255, 0.0/255);
	glTranslatef(0,44,5);
	glRotatef(-40,1,0,0);
	glutSolidTorus(1,8,70,70);
	glPopMatrix();
	//brows
	glPushMatrix();
	glColor3f(0.0/255, 0.0/255, 0.0/255);
	glTranslatef(2.3,59,7.3);
	glRotatef(70,1,0,0);
	glutSolidTorus(0.5,3,70,70);
	glPopMatrix();
	glPushMatrix();
	glColor3f(0.0/255, 0.0/255, 0.0/255);
	glTranslatef(-2.3,59,7.3);
	glRotatef(70,1,0,0);
	glutSolidTorus(0.5,3,70,70);
	glPopMatrix();
	//nose
	glPushMatrix();
	glTranslatef(0,27,0);
	glColor3f(210.0/255,180.0/255,140.0/255);
	glTranslatef(0,19,10);
	glutSolidSphere(4,70,70);
	glPopMatrix(); 
	//eye 1
	glPushMatrix();
	glTranslatef(0,28,0);
	glColor3f(255.0/255, 255.0/255, 255.0/255);
	glTranslatef(-3,26,12.1);
	glScalef(1,1.7,1);
	glutSolidSphere(2.6,70,70);
	glPopMatrix(); 
	glPushMatrix();
	glTranslatef(0,28,0);
	glColor3f(0.0/255, 0.0/255, 0.0/255);
	glTranslatef(-3,25.5,14);
	glScalef(1,1.7,1);
	glutSolidSphere(1.0,70,70);
	glPopMatrix(); 
	//eye 2
	glPushMatrix();
	glTranslatef(0,28,0);
	glColor3f(255.0/255, 255.0/255, 255.0/255);
	glTranslatef(3,26,12.1);
	glScalef(1,1.7,1);
	glutSolidSphere(2.6,70,70);
	glPopMatrix(); 
	glPushMatrix();
	glTranslatef(0,28,0);
	glColor3f(0.0/255, 0.0/255, 0.0/255);
	glTranslatef(3,25.5,14);
	glScalef(1,1.7,1);
	glutSolidSphere(1.0,70,70);
	glPopMatrix();
	glPopMatrix(); 
	///////////////////////////////////////////////////////////////
	//	Neck
	///////////////////////////////////////////////////////////////
	glPushMatrix();
	glTranslatef(0,25,0);
	glColor3f(255.0/255, 255.0/255, 255.0/255);
	glTranslatef(0,4,0);
	glRotatef(-90,1,0,0);
	glutSolidTorus(2.5,7,70,70);
	glPopMatrix();
	glPushMatrix();
	glTranslatef(0,25,0);
	glColor3f(255.0/255, 255.0/255, 255.0/255);
	glTranslatef(0,7,0);
	glRotatef(-90,1,0,0);
	glutSolidTorus(2.5,7,70,70);
	glPopMatrix();
	glPushMatrix();
	glTranslatef(0,25,0);
	glColor3f(255.0/255, 255.0/255, 255.0/255);
	glTranslatef(0,10,0);
	glRotatef(-90,1,0,0);
	glutSolidTorus(2.5,7,70,70);
	glPopMatrix();
	///////////////////////////////////////////////////////////////
	//	Body
	///////////////////////////////////////////////////////////////

	glPushMatrix();
	//glColor3f(130.0/255, 130.0/255, 130.0/255);
	glColor3f(139.0/255,35.0/255,35.0/255);
	glScalef(1,1.3,1);							//24*1.3 =31.2
	glutSolidSphere(24,70,70);
	glPopMatrix(); 



	///////////////////////////////////////////////////////////////
	//	Heands
	///////////////////////////////////////////////////////////////
	///////////////////////////////////////////////////////////////
	//	Right Hand
	///////////////////////////////////////////////////////////////

	glPushMatrix();					

	glTranslatef(0,11,0);
	glRotatef(hand2_move,1,0,0);
	glTranslatef(0,-11,0);			
	//--------------------------
	
	glPushMatrix();
	glColor3f(255.0/255, 255.0/255, 255.0/255);
	glTranslatef(-28,10,0);
	glutSolidSphere(6,70,70);
	glPopMatrix(); 
	glPushMatrix();
	glColor3f(255.0/255, 255.0/255, 255.0/255);
	glTranslatef(-20,10,0);
	glutSolidSphere(6,70,70);
	glPopMatrix(); 
	
	glPushMatrix();
	glColor3f(139.0/255,35.0/255,35.0/255);
	//glColor3f(130.0/255, 130.0/255, 130.0/255);
	glTranslatef(-29,-14,0);
	glScalef(1,5,1);
	glutSolidSphere(5,70,70);
	glPopMatrix(); 
	glPopMatrix(); 
	///////////////////////////////////////////////////////////////
	//	Left Hand
	///////////////////////////////////////////////////////////////
	glPushMatrix();					

	glTranslatef(0,11,0);
	glRotatef(hand1_move,1,0,0);
	glTranslatef(0,-11,0);		
	//--------------------------
	
	glPushMatrix();
	glColor3f(255.0/255, 255.0/255, 255.0/255);
	glTranslatef(28,10,0);
	glutSolidSphere(6,70,70);
	glPopMatrix(); 
	glPushMatrix();
	glColor3f(255.0/255, 255.0/255, 255.0/255);
	glTranslatef(20,10,0);
	glutSolidSphere(6,70,70);
	glPopMatrix(); 
	
	glPushMatrix();
	glColor3f(139.0/255,35.0/255,35.0/255);
	//glColor3f(130.0/255, 130.0/255, 130.0/255);
	glTranslatef(29,-12,0);
	glScalef(1,5,1);
	glutSolidSphere(5,70,70);
	glPopMatrix(); 

	glPopMatrix();	
	glPopMatrix();	
	///////////////////////////////////////////////////////////////
	//	Legs
	///////////////////////////////////////////////////////////////
	///////////////////////////////////////////////////////////////
	//	Right Leg
	///////////////////////////////////////////////////////////////
	//leg
	glPushMatrix();		
	
	glTranslatef(0,-31,0);			//31 = 52 - (3.5*6)[3.5 *aktina]
	glRotatef(leg1_move,1,0,0);
	glTranslatef(0,31,0);
	//------------------------------
	glPushMatrix();
	glColor3f(139.0/255,35.0/255,35.0/255);
	glTranslatef(-8,-52,0);
	glScalef(1,3.5,1);
	glutSolidSphere(6,70,70);
	glPopMatrix(); 
	//enwsh
	glPushMatrix();
	glColor3f(255.0/255, 255.0/255, 255.0/255);
	glTranslatef(-8,-30,0);
	glutSolidSphere(6,70,70);
	glPopMatrix(); 
	//shoe
	glPushMatrix();
	glColor3f(130.0/255, 130.0/255, 130.0/255);
	glTranslatef(-8,-79,5);
	glScalef(3,2,7);
	glutSolidCube(3.0);
	glPopMatrix(); 
	//sock
	glPushMatrix();
	glColor3f(255.0/255, 255.0/255, 255.0/255);
	glTranslatef(-8,-74,0);
	glutSolidSphere(4,70,70);
	glPopMatrix(); 

	glPopMatrix(); 
	///////////////////////////////////////////////////////////////
	//	Left Leg
	///////////////////////////////////////////////////////////////	
	glPushMatrix();		
	
	glTranslatef(0,-31,0);
	glRotatef(leg2_move,1,0,0);
	glTranslatef(0,31,0);
	//---------------------------------
	//leg
	glPushMatrix();
	glColor3f(139.0/255,35.0/255,35.0/255);
	glTranslatef(8,-52,0);
	glScalef(1,3.5,1);
	glutSolidSphere(6,70,70);
	glPopMatrix(); 
	//enwsh
	glPushMatrix();
	glColor3f(255.0/255, 255.0/255, 255.0/255);
	glTranslatef(8,-30,0);
	glutSolidSphere(6,70,70);
	glPopMatrix(); 
	//shoe
	glPushMatrix();
	glColor3f(130.0/255, 130.0/255, 130.0/255);
	glTranslatef(8,-79,5);
	glScalef(3,2,7);
	glutSolidCube(3.0);
	glPopMatrix(); 
	//sock
	glPushMatrix();
	glColor3f(255.0/255, 255.0/255, 255.0/255);
	glTranslatef(8,-74,0);
	glutSolidSphere(4,70,70);
	glPopMatrix(); 

	glPopMatrix(); 

glPopMatrix(); 
}
/*************************************************************/
/***         ROAD CREATION								   ***/
/*************************************************************/

void road_creation(){
	glPushMatrix();
	if(car_mode == false)
		glColor3f(151.0/255,105.0/255,79.0/255);
	else 
		glColor3f(130.0/255,130.0/255,130.0/255);
	glTranslatef(50.0, -94.0, 0.0);
	glScalef(120,7,700);
	glutSolidCube(3.0);
	glPopMatrix();
}
/*************************************************************/
/***         BARRIER CREATION							   ***/
/*************************************************************/
void barrier_creation(){
	glPushMatrix();
	glTranslatef(0.0, -4.0, Item_passing);			
	
	
	glPushMatrix();
	glTranslatef(-30.0, 0.0, 0);	

	glPushMatrix();
	glTranslatef(70.0, -55.0, 140);	
	glColor3f(189.0/255,183.0/255,107.0/255);
	glScalef(7,90,7);
	glutSolidCube(1.0);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(70.0, -14.0, 140);
	glColor3f(189.0/255,183.0/255,107.0/255);
	glScalef(1,1.3,1);
	glRotatef(-90,1,0,0);
	glutSolidCone(6,20,60,60);			//26 -14
	glPopMatrix();

	glPopMatrix();
	/////////////barrier
	glPushMatrix();
	glTranslatef(-40.0, 0.0, 0);	
	
	glPushMatrix();
	glTranslatef(70.0, -55.0, 140);	
	glColor3f(189.0/255,183.0/255,107.0/255);
	glScalef(7,90,7);
	glutSolidCube(1.0);
	glPopMatrix();
	
	glPushMatrix();
	glTranslatef(70.0, -14.0, 140);
	glColor3f(189.0/255,183.0/255,107.0/255);
	glScalef(1,1.3,1);
	glRotatef(-90,1,0,0);
	glutSolidCone(6,20,60,60);
	glPopMatrix();

	glPopMatrix();
	/////////////barrier
	glPushMatrix();
	glTranslatef(-50.0, 0.0, 0);	
	
	glPushMatrix();
	glTranslatef(70.0, -55.0, 140);	
	glColor3f(189.0/255,183.0/255,107.0/255);
	glScalef(7,90,7);
	glutSolidCube(1.0);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(70.0, -14.0, 140);
	glColor3f(189.0/255,183.0/255,107.0/255);
	glScalef(1,1.3,1);
	glRotatef(-90,1,0,0);
	glutSolidCone(6,20,60,60);
	glPopMatrix();

	glPopMatrix();
	/////////////barrier
	glPushMatrix();
	glTranslatef(-60.0, 0.0, 0);	

	glPushMatrix();
	glTranslatef(70.0, -55.0, 140);	
	glColor3f(189.0/255,183.0/255,107.0/255);
	glScalef(7,90,7);
	glutSolidCube(1.0);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(70.0, -14.0, 140);
	glColor3f(189.0/255,183.0/255,107.0/255);
	glScalef(1,1.3,1);
	glRotatef(-90,1,0,0);
	glutSolidCone(6,20,60,60);
	glPopMatrix();

	glPopMatrix();
	/////////////barrier
	glPushMatrix();
	glTranslatef(-70.0, 0.0, 0);	
	
	glPushMatrix();
	glTranslatef(70.0, -55.0, 140);	
	glColor3f(189.0/255,183.0/255,107.0/255);
	glScalef(7,90,7);
	glutSolidCube(1.0);
	glPopMatrix();
	//korifh
	glPushMatrix();
	glTranslatef(70.0, -14.0, 140);
	glColor3f(189.0/255,183.0/255,107.0/255);
	glScalef(1,1.3,1);
	glRotatef(-90,1,0,0);
	glutSolidCone(6,20,60,60);
	glPopMatrix();

	glPopMatrix();
	/////////////barrier
	glPushMatrix();
	glTranslatef(-80.0, 0.0, 0);	
	
	glPushMatrix();
	glTranslatef(70.0, -55.0, 140);	
	glColor3f(189.0/255,183.0/255,107.0/255);
	glScalef(7,90,7);
	glutSolidCube(1.0);
	glPopMatrix();
	//korifh
	glPushMatrix();
	glTranslatef(70.0, -14.0, 140);
	glColor3f(189.0/255,183.0/255,107.0/255);
	glScalef(1,1.3,1);
	glRotatef(-90,1,0,0);
	glutSolidCone(6,20,60,60);
	glPopMatrix();

	glPopMatrix();
	/////////////barrier
	glPushMatrix();
	glTranslatef(-90.0, 0.0, 0);	
	
	glPushMatrix();
	glTranslatef(70.0, -55.0, 140);	
	glColor3f(189.0/255,183.0/255,107.0/255);
	glScalef(7,90,7);
	glutSolidCube(1.0);
	glPopMatrix();
	
	glPushMatrix();
	glTranslatef(70.0, -14.0, 140);
	glColor3f(189.0/255,183.0/255,107.0/255);
	glScalef(1,1.3,1);
	glRotatef(-90,1,0,0);
	glutSolidCone(6,20,60,60);
	glPopMatrix();

	glPopMatrix();
	/////////////barrier
	glPushMatrix();
	glTranslatef(-100.0, 0.0, 0);	

	glPushMatrix();
	glTranslatef(70.0, -55.0, 140);	
	glColor3f(189.0/255,183.0/255,107.0/255);
	glScalef(7,90,7);
	glutSolidCube(1.0);
	glPopMatrix();
	
	glPushMatrix();
	glTranslatef(70.0, -14.0, 140);
	glColor3f(189.0/255,183.0/255,107.0/255);
	glScalef(1,1.3,1);
	glRotatef(-90,1,0,0);
	glutSolidCone(6,20,60,60);
	glPopMatrix();

	glPopMatrix();
	/////////////barrier
	glPushMatrix();
	glTranslatef(-110.0, 0.0, 0);	
	
	glPushMatrix();
	glTranslatef(70.0, -55.0, 140);	
	glColor3f(189.0/255,183.0/255,107.0/255);
	glScalef(7,90,7);
	glutSolidCube(1.0);
	glPopMatrix();
	
	glPushMatrix();
	glTranslatef(70.0, -14.0, 140);
	glColor3f(189.0/255,183.0/255,107.0/255);
	glScalef(1,1.3,1);
	glRotatef(-90,1,0,0);
	glutSolidCone(6,20,60,60);
	glPopMatrix();

	glPopMatrix();
	glPopMatrix(); 
}
/*************************************************************/
/***        INFO()										   ***/
/*************************************************************/
void Info(){
	float var;
	glPushMatrix(); 
	glTranslatef(0.0, -20, 0.0);
	glColor3f(1,1,1);

	if(pause == true){
		glPushMatrix();
		for_color_pause = true;
		keimeno("PAUSED",0.3,0);
		for_color_pause = false;
		glPopMatrix();
	}
	glPushMatrix();
   	 glColor3f(1,1,1);
	 glTranslatef(0.0, 24.0, 0.0);
	if(Enable_flip == true)
		keimeno("Flip at speed:8 Enabled",0.023f,0.005);
	else
		keimeno("Flip at speed:8 Disabled",0.023f,0.005);
	glPopMatrix();
	if (message == true){
		keimeno2("!!! OOOOOUCH !!!",0.05f);	
	}
	if (message_car == true){
		keimeno2("!!! OOOOOUCH !!!",0.05f);	
	}
	glPushMatrix();
	glColor3f(1,1,1);
    glTranslatef(0.0, 12.0, 0.0);
	if (jump == true)
		var = forhelp;					
	else
		var = LegSpeed;
	if(var == 1 )
		keimeno("Speed: 1",0.03f,0.05);
	else if(var == 2 )
		keimeno("Speed: 2",0.03f,0.05);
	else if(var == 3 )
		keimeno("Speed: 3",0.03f,0.05);
	else if(var == 4 )
		keimeno("Speed: 4",0.03f,0.05);
	else if(var == 5 )
		keimeno("Speed: 5",0.03f,0.05);
	else if(var == 6 )
		keimeno("Speed: 6",0.03f,0.05);
	else if(var == 7 )
		keimeno("Speed: 7",0.03f,0.05);
	else if(var == 8 )
		keimeno("Speed: 8",0.03f,0.05);
	glPopMatrix();

	glPushMatrix();
    glTranslatef(0.0, 40.0, 0.0);
	keimeno("Zoom : +/- ",0.023f,0.0);
	glPopMatrix();

	glPushMatrix();
    glTranslatef(0.0, 45.0, 0.0);
	keimeno("Pause: Esc ",0.023f,0.0);
	glPopMatrix();

	glPushMatrix();
    glTranslatef(0.0, 50.0, 0.0);
	keimeno("Enable Car Mode : press 1 ",0.023f,0.0);
	glPopMatrix();

	glPushMatrix();
    glTranslatef(0.0, 61, 0.0);
	keimeno("'G' to Disable car mode grass(for LAG)",0.023f,0.0);
	glPopMatrix();

	glPushMatrix();
    glTranslatef(0.0, 56.0, 0.0);
	if(car_mode == true)
		keimeno("Car Mode : ENABLED ",0.023f,0.005);
	else
		keimeno("Car Mode : DISABLED ",0.023f,0.005);
	glPopMatrix();

	glPushMatrix();
    glTranslatef(0.0, 34.5, 0.0);
	keimeno("Jump : Space ",0.023f,0.005);
	glPopMatrix();
	glPushMatrix();

    glTranslatef(0.0, 29, 0.0);
	keimeno("Flip : 'F' ",0.023f,0.005);
	glPopMatrix();
	if (eleos == true && pagwse == false){ 
		engine->play2D("hit.mp3", false);
		Sleep(2000);	
		pagwse = true;		
	}


	glPopMatrix();
}
/*************************************************************/
/***        tree_creation()								   ***/
/*************************************************************/
void tree_creation(float  passing,int i){
	glPushMatrix();
	glTranslatef(90,-92.0,passing);

	if(i==0 || i==3)
		glScaled(274,274,274);
	else if(i==1)
		glScaled(374,274,374);
	else if(i==2)
		glScaled(274,374,274);
	else if(i==4)
		glScaled(174,174,174);
	
	DisplayModel(md);

	glPopMatrix();



}
/*************************************************************/
/***        grass_creation()								   ***/
/*************************************************************/
void grass_creation(){		
glPushMatrix();
	//glTranslatef(0,0,Tree_passing[1]);
	glPushMatrix();
	glTranslatef(0,0,-800);
	glTranslatef(-116,0,0);
	glTranslatef(0,-86,0);
	glRotatef(-90,0,1,0);
	glScaled(11,11,11);
	DisplayModel2(grass);
	glPopMatrix(); 

	glPushMatrix();
	glTranslatef(0,0,-800);
	glTranslatef(-116,0,0);
	glTranslatef(0,-86,0);
	glRotatef(90,0,1,0);
	glScaled(11,11,11);
	DisplayModel2(grass);
	glPopMatrix(); 

	glPushMatrix();
	glTranslatef(0,0,-400);
	glTranslatef(-116,0,0);
	glTranslatef(0,-86,0);
	glRotatef(-90,0,1,0);
	glScaled(11,11,11);
	DisplayModel2(grass);
	glPopMatrix(); 

	glPushMatrix();
	glTranslatef(0,0,-400);
	glTranslatef(-116,0,0);
	glTranslatef(0,-86,0);
	glRotatef(90,0,1,0);
	glScaled(11,11,11);
	DisplayModel2(grass);
	glPopMatrix(); 

	glPushMatrix();
	glTranslatef(0,0,800);
	glTranslatef(-116,0,0);
	glTranslatef(0,-86,0);
	glRotatef(-90,0,1,0);
	glScaled(11,11,11);
	DisplayModel2(grass);
	glPopMatrix(); 

	glPushMatrix();
	glTranslatef(0,0,800);
	glTranslatef(-116,0,0);
	glTranslatef(0,-86,0);
	glRotatef(90,0,1,0);
	glScaled(11,11,11);
	DisplayModel2(grass);
	glPopMatrix(); 

	glPushMatrix();
	glTranslatef(0,0,400);
	glTranslatef(-116,0,0);
	glTranslatef(0,-86,0);
	glRotatef(-90,0,1,0);
	glScaled(11,11,11);
	DisplayModel2(grass);
	glPopMatrix(); 

	glPushMatrix();
	glTranslatef(0,0,400);
	glTranslatef(-116,0,0);
	glTranslatef(0,-86,0);
	glRotatef(90,0,1,0);
	glScaled(11,11,11);
	DisplayModel2(grass);
	glPopMatrix(); 

	glPushMatrix();
	glTranslatef(-116,0,0);
	glTranslatef(0,-86,0);
	glRotatef(-90,0,1,0);
	glScaled(11,11,11);
	DisplayModel2(grass);
	glPopMatrix(); 

	glPushMatrix();
	glTranslatef(-116,0,0);
	glTranslatef(0,-86,0);
	glRotatef(90,0,1,0);
	glScaled(11,11,11);
	DisplayModel2(grass);
	glPopMatrix(); 
glPopMatrix(); 

}
void all_grass(){

	glPushMatrix();
	glTranslatef(330,0,0);
	grass_creation();
glPopMatrix(); 
grass_creation();
}
/*************************************************************/
/***        car_creation()								   ***/
/*************************************************************/
void car_creation(){
	glPushMatrix();
		glTranslatef(0.0, 0, car_passing);

		glTranslatef(0,-84,0);
		glRotatef(180,0,1,0);
		glRotatef(-90,1,0,0);
		glScaled(80,80,80);
		DisplayModel2(car);
	glPopMatrix(); 
}
/*************************************************************/
/*************************************************************/
/***        RENDER()									   ***/
/*************************************************************/
/*************************************************************/
void Render()
{   
	int i;

	glClear(GL_COLOR_BUFFER_BIT);
	glClear(GL_DEPTH_BUFFER_BIT);
	  
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
    glTranslatef(0.0, 0.0, -200.0);
	

	glPushMatrix();
	  glTranslatef(0,0,zoom);
	  glRotatef(Rotate_in_x,1,0,0);		
	  glRotatef(Rotate_in_y,0,1,0);		

					
  	  create_character(LegMovement,LegMovement2,Tilted_front,LegMovement,LegMovement2);  
	  for(i=0;i<5;i++)
		tree_creation(Tree_passing[i],i);	
	
	  if(car_mode == false)
		barrier_creation();			
	  else{
   	   if(grass_mode == true)
		   all_grass();
		car_creation();
	  }

	 

	  road_creation();
	glPopMatrix(); 		
	
	Info();						


	glutSwapBuffers();
}

//-----------------------------------------------------------


void Idle()  //animations
{
if(pause == false){
	
	static bool flag_1 = false;
	static bool flag_2 = false;

	if (LegMovement <= -50){     
			flag_1 = true;
			LegMovement = -50;
	}
	if (LegMovement >= 35 ){
			flag_1 = false;
			LegMovement = 35;
	}

	if(flag_1 == false)
		LegMovement -= LegSpeed;
	else
		LegMovement += LegSpeed;


	if (LegMovement2 <= -50){
			flag_2 = true;
			LegMovement2 = -50;
	}
	if (LegMovement2 >= 35 ){
			flag_2 = false;
			LegMovement2 = 35;
	}

	if(flag_2 == false)
		LegMovement2 -= LegSpeed;
	else
		LegMovement2 += LegSpeed;

	float g = 10;
	float dt = 0.1;
	static float temp;


	if (jump == true){

		if(first == false){
					//printf("v = %f\n",v);
			temp = LegSpeed;		
			forhelp = temp;
			if(LegSpeed <5)			
				LegSpeed = 1;
			else
				LegSpeed =2;
			first = true;}

		if (v*dt < 0.0) negative = true;


		if (TranslateY<0)
			v=-v;
		else	
			v=v-g*dt;
		TranslateY=TranslateY + v*dt;


		if(v*dt >=0 && negative == true ){
			LegSpeed = temp;
			jump = false;
		}

		
	}
	if( flip == true){		
		fliping+=3;
		if (fliping == 360){
			fliping = 0.0;
			flip = false;
		}
	}	
	float check ;
	check = LegSpeed;
	static int counts = 0;
	static bool entered = false;
	static int counts_car = 0;
	static bool entered_car = false;
for(int j=0;j<5;j++)							
	if( Tree_passing[j]<= -800)
		Tree_passing[j] = 600;

if(Item_passing <= -800) Item_passing = 650;		
if(car_passing <= -1900) car_passing = 850;		


	if (jump == true)
		check = forhelp;		
	if(check == 1){				
		if(car_mode == false)Item_passing -=0.5;
		car_passing -=0.5;
		for(int j=0;j<5;j++)
			Tree_passing[j] -= 0.5;
	}
	else if (check == 2 ){
		if(car_mode == false)Item_passing -=1;
		car_passing -=1;
		for(int j=0;j<5;j++)
			Tree_passing[j] -= 1;
	}
	else if (check == 3 ){
		if(car_mode == false)Item_passing -=1.5;
		car_passing -=1.5;
		for(int j=0;j<5;j++)
			Tree_passing[j] -= 1.5;
	}
	else if (check == 4 ){
		if(car_mode == false)Item_passing -=2;
		car_passing -=2;
		for(int j=0;j<5;j++)
			Tree_passing[j] -= 2;
	}
	else if (check == 5 ){
		if(car_mode == false)Item_passing -=2.5;
		car_passing -=2.5;
		for(int j=0;j<5;j++)
			Tree_passing[j] -= 2.5;
	}
	else if (check == 6 ){
		if(car_mode == false)Item_passing -=3;
		car_passing -=3;
		for(int j=0;j<5;j++)
			Tree_passing[j] -= 3;
	}
	else if (check == 7 ){
		if(car_mode == false)Item_passing -=3.5;
		car_passing -=3.5;
		for(int j=0;j<5;j++)
			Tree_passing[j] -= 3.5;
	}
	else if (check == 8 ){
		if(car_mode == false)Item_passing -=4;
		car_passing -=4;
		for(int j=0;j<5;j++)
			Tree_passing[j] -= 4;
	}

if(car_mode == true)
	Item_passing = 650;
if(car_mode == false)
	car_passing = 850;

	car_passing-= 10;

	eleos = false;

	if (car_mode == true  -79+TranslateY <= 23-18 && car_passing <=135 && car_passing >=-180){
		entered_car = true;
		counts_car ++;
		eleos = true;
		message_car = true;
	}


	if (flip == false && -79+TranslateY <= 26-18 && Item_passing <=-90 && Item_passing >=-160){
		entered = true;
		counts ++;
		eleos = true;
		message = true;
	}
	if (flip == true && -79+TranslateY+20 <= -10 && Item_passing <=-90 && Item_passing >=-160){
		entered = true;
		counts ++;
		eleos = true;
		message = true;
	}
	if(entered == true && eleos == false){
		counts = 0;
		message = false;
		pagwse = false;
	}
	if(counts == 1 || counts == 2)			
		eleos = false;

	if(entered_car == true && eleos == false){
		counts_car = 0;
		message_car = false;
		pagwse = false;
	}
	if(counts_car == 1 || counts_car == 2)			
		eleos = false;
	}


		glutPostRedisplay(); 
		//closing pause here
}
//------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------
void Keyboard(unsigned char key,int x,int y)		
{

	if(key == 27){
		if(pause == true)
			pause = false;
		else if(pause == false)
			pause = true;

	//	while(pause == true)			  
		//	Sleep(1);
		
	}
if(pause == false){
	if(key == 'g')
		if(grass_mode == false)
			grass_mode = true;
		else
			grass_mode = false;

	if(key == '1')
		if(car_mode == false)
			car_mode = true;
		else
			car_mode = false;

	
	if(key == 'f'){
		if(Enable_flip == false)
			Enable_flip = true;
		else
			Enable_flip = false;
	}
	if(key == 32 && jump == false){           //space bar
		negative = false;	
		first = false;
		if(LegSpeed == 1 || LegSpeed == 2)
		v = 40;
		else if(LegSpeed == 3 || LegSpeed == 4)
		v = 45;
		else if( LegSpeed == 5 || LegSpeed == 6)
		v = 50;
		else if (LegSpeed == 7 )
		v = 55;
		else if( LegSpeed ==8)
		v = 60;

		jump = true;
		if(Enable_flip == true && LegSpeed == 8)	//for flip effect
			flip = true;
		///sound effect

		if(flip == false )
		          engine->play2D("jump.mp3", false);
		else
		          engine->play2D("flip.mp3", false);

	}
	if(key == '='&& zoom <= -15){
		zoom+=5;
	//	cout<<zoom<<endl;
	}
	if(key == '-' && zoom >= -450){
		zoom-=5;
	//	cout<<zoom<<endl;
	}
	glutPostRedisplay();
}		//closing pause here!
}

void special(int key, int x, int y)		
{
	if(pause == false){
	
	static int counter = 1;

	if (key == GLUT_KEY_UP && jump == false){ 
		if(counter < 8)
			counter++;

	}
	if (key == GLUT_KEY_DOWN && jump == false){
		if(counter > 1)
			counter--;
	}
	if(jump == false){
	LegSpeed = counter;
	if(counter == 1)
		Tilted_front = 4;
	else if(counter == 2)
		Tilted_front = 5;
	else if(counter == 3)
		Tilted_front = 6;
	else if(counter == 4)
		Tilted_front = 10;
	else if(counter == 5)
		Tilted_front =14;
	else if(counter == 6)
		Tilted_front =18;
	else if(counter == 7)
		Tilted_front =22;
	else if(counter == 8)
		Tilted_front =26;
	}
	//glutPostRedisplay();
	}		
}

void Mouse(int button,int state,int x,int y)	
{
	if(pause == false){
	
	 if(state == GLUT_DOWN && button == GLUT_LEFT_BUTTON)
		R_y = true;
	 else{
		 mouse_vision_y = true;
		R_y = false;
	 }

	 if(state == GLUT_DOWN && button == GLUT_RIGHT_BUTTON)
		R_x = true;
	 else{
		mouse_vision_x = true;
		R_x = false;
	 }

	}
}
void Motion(int x, int y){		
if(pause == false){
	
static float temp_x = x ;
static float temp_y = y ;


	if(R_y == true){
		if(mouse_vision_y == true){
			temp_x = x;
			mouse_vision_y = false;
		}
		Rotate_in_y += x - temp_x;
	}


	if(R_x == true){
		if(mouse_vision_x == true){
			temp_y = y;
			mouse_vision_x = false;
		}
		Rotate_in_x += y-temp_y;
	}
temp_x = x;
temp_y = y;

}
}

//------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------
void Resize(int w, int h)			
{ 

	global_w = w;
	global_h = h;


	// define the visible area of the window ( in pixels )
	if (h==0) 
		h=1;

	glViewport(0,0,w,h); 

	// Setup viewing volume

	glMatrixMode(GL_PROJECTION); 
	glLoadIdentity();
	 

	float aspect = (float)w/(float)h;             /// aspect ratio
	gluPerspective(60.0, aspect, 1.0, 1150.0);

}

void keimeno(const char *str,float size,float off)	
{
	glPushMatrix();

if(for_color_pause == false){
	glColor3f(1.0, 1.0, 1.0);	
	glTranslatef(-120.0,-60.0,50.0);
}
else{
	glTranslatef(-90.0,0.0,50.0);
	glColor3f(185.0/255, 211.0/255, 238.0/255);	
}

	//glTranslatef(-1*global_w/8.33,-1*global_h/11.66,50.0);

	
	
	glScalef(size,size+off,size);

	for (int i=0;i<strlen(str);i++)
	  glutStrokeCharacter(GLUT_STROKE_MONO_ROMAN,str[i]);
	glPopMatrix();

}
void keimeno2(const char *str,float size)
{

	glPushMatrix();

	glColor3f(1.0, 1.0, 1.0);
	
	glTranslatef(0.0,30.0,50.0);

	glScalef(size,size+0.1,size);

	for (int i=0;i<strlen(str);i++)
	  glutStrokeCharacter(GLUT_STROKE_MONO_ROMAN,str[i]);
	glPopMatrix();

}
///////////////////////////////////////////////////////////////////////////
//////////				READING FROM .OBJ FILE THE TREE
///////////////////////////////////////////////////////////////////////////

void ReadFile(model *md){
	ifstream obj_file("tree.obj");                   // Open the file for reading OBJINFO.TXT

	int counter=0;
	char tmp[15];
	md->vertices = 0;
	md->normals = 0;
	md->faces = 0;

	while (obj_file != NULL){			
		obj_file >> tmp;

		if( strcmp(tmp,"v") == 0)
			(md->vertices)++;
		else if( strcmp(tmp,"vn") == 0)
			(md->normals)++;
		else if( strcmp(tmp,"f") == 0)
			(md->faces)++;
	}
   obj_file.close();

	
	ifstream obj_filee("tree.obj");		

	int v=0,vn=0,f=0;		//counters
	char c;

	md->obj_points = new point[md->vertices];
	md->obj_normals = new normal[md->normals];
	md->obj_faces = new face[md->faces];

	while (obj_filee != NULL){
		obj_filee >> tmp;

		if( strcmp(tmp,"v") == 0){
			obj_filee >> md->obj_points[v].x;			//read and put in the correct place 
			obj_filee >> md->obj_points[v].y;
			obj_filee >> md->obj_points[v].z;
			v++;
		}
		else if( strcmp(tmp,"vn") == 0){
			obj_filee >> md->obj_normals[vn].x;			//read and put in the correct place 
			obj_filee >> md->obj_normals[vn].y;
			obj_filee >> md->obj_normals[vn].z;
			vn++;
		}
		else if( strcmp(tmp,"f") == 0){
			obj_filee >> md->obj_faces[f].v[0];			//read and put in the correct place 
			obj_filee >> c;obj_filee >>c;				//trow tis //
			obj_filee >> md->obj_faces[f].vn[0];
			
			obj_filee >> md->obj_faces[f].v[1];			//read and put in the correct place 
			obj_filee >> c;obj_filee >>c;
			obj_filee >> md->obj_faces[f].vn[1];
		
			obj_filee >> md->obj_faces[f].v[2];			//read and put in the correct place 
			obj_filee >> c;obj_filee >>c;
			obj_filee >> md->obj_faces[f].vn[2];
			f++;
		}
	}
obj_filee.close();

}
///////////////////////////////////////////////////////////////////////////
//////////				READING THE .OBJ CAR 
///////////////////////////////////////////////////////////////////////////
void ReadFile2(model *md,string name){
	string obj_name = name ;
	string mtl_name = name;
	obj_name +=".obj";
	mtl_name +=".mtl";

	ifstream obj_file2(obj_name);                   // Open the file for reading OBJINFO.TXT
	 bool first = true;
	 bool bike =false;
	bool ano =false;
	char x1,x2;
	int counter=0;
	char tmp[55];
	char elenxos[55];
	char eating[55];
	float pff;
	md->vertices = 0;
	md->normals = 0;
	md->faces = 0;

	while (obj_file2 != NULL){
		obj_file2 >> tmp;

		if( strcmp(tmp,"v") == 0)
			(md->vertices)++;
		else if( strcmp(tmp,"vn") == 0)
			(md->normals)++;
		else if( strcmp(tmp,"f") == 0)
			(md->faces)++;
	}
   obj_file2.close();	
	ifstream obj_filee(obj_name);  
	ifstream mtl_file(mtl_name);

	int v=0,vn=0,f=0;		//counters
	char c;
	int eat;
	int ca = 0;
	int a=0;
	float r,g,b;
	md->color_ = new col[md->faces];
	md->obj_points = new point[md->vertices];
	md->obj_normals = new normal[md->normals];
	md->obj_faces = new face[md->faces];

	while (obj_filee != NULL){
		obj_filee >> tmp;
		
	float  Ka,Kd,Ks;
			if (strcmp(tmp,"usemtl") == 0){
				obj_filee >> tmp;
					while (mtl_file != NULL){
						mtl_file >> elenxos;
						if(strcmp(elenxos,"newmtl") == 0){			
							mtl_file >> elenxos;						

						if(strcmp(elenxos,tmp) == 0){			
							mtl_file >> elenxos;

							while (strcmp(elenxos,"Ka") != 0){			
								mtl_file >> elenxos;
							}
							mtl_file >> Ka;			
							r = Ka;
							mtl_file>>pff;mtl_file>>pff;mtl_file>>eating;
							mtl_file >> Kd;	
							g = Kd;
							mtl_file>>pff;mtl_file>>pff;mtl_file>>eating;
							mtl_file >> Ks;	
							b = Ks;

							
							break;
						}
						}
						}
			}
			mtl_file.clear();
			mtl_file.seekg( 0 );


		if( strcmp(tmp,"v") == 0){
			obj_filee >> md->obj_points[v].x;			//read and put in the correct place 
			obj_filee >> md->obj_points[v].y;
			obj_filee >> md->obj_points[v].z;
			v++;
		}
		else if( strcmp(tmp,"vn") == 0){
			obj_filee >> md->obj_normals[vn].x;			//read and put in the correct place 
			obj_filee >> md->obj_normals[vn].y;
			obj_filee >> md->obj_normals[vn].z;
			vn++;
		}
		else if( strcmp(tmp,"f") == 0){
			
			md->color_[ca].r=r;
			md->color_[ca].g=g;
			md->color_[ca].b=b;
			ca++;
			obj_filee >> md->obj_faces[f].v[0];			//read and put in the correct place 
			obj_filee >> c;
			obj_filee >> md->obj_faces[f].vn[0];
			obj_filee >> c;obj_filee >> eat;
			obj_filee >> md->obj_faces[f].v[1];			//read and put in the correct place 
			obj_filee >> c;
			obj_filee >> md->obj_faces[f].vn[1];
			obj_filee >> c;obj_filee >> eat;
			obj_filee >> md->obj_faces[f].v[2];			//read and put in the correct place 
			obj_filee >> c;
			obj_filee >> md->obj_faces[f].vn[2];
			obj_filee >> c;obj_filee >> eat;
			f++;
		}
	}
	
}
///////////////////////////////////////////////////////////////////////////
//////////				DISPLAYING THE .OBJ TREE ABOVE
///////////////////////////////////////////////////////////////////////////
void DisplayModel(model md)
{static int sum = 0;
sum+=md.faces;
	static bool efe=false;
	float z;
	glPushMatrix();
	glBegin(GL_TRIANGLES);

	for (int i = 0; i < md.faces; i++)
	{z=i+400;
		
		//if(i%2 == 0) 
			glColor3f(0.0/255, (float)z/2/255,127.0/255);		
		//else 
		//	glColor3f(255.0/255, 255.0/255, 255.0/255); 

		glNormal3f(md.obj_normals[md.obj_faces[i].vn[0]-1].x,md.obj_normals[md.obj_faces[i].vn[0]-1].y,md.obj_normals[md.obj_faces[i].vn[0]-1].z);
		glNormal3f(md.obj_normals[md.obj_faces[i].vn[1]-1].x,md.obj_normals[md.obj_faces[i].vn[1]-1].y,md.obj_normals[md.obj_faces[i].vn[1]-1].z);
		glNormal3f(md.obj_normals[md.obj_faces[i].vn[2]-1].x,md.obj_normals[md.obj_faces[i].vn[2]-1].y,md.obj_normals[md.obj_faces[i].vn[2]-1].z);
		
		glVertex3f(md.obj_points[md.obj_faces[i].v[0]-1].x, md.obj_points[md.obj_faces[i].v[0]-1].y,md.obj_points[md.obj_faces[i].v[0]-1].z);
		glVertex3f(md.obj_points[md.obj_faces[i].v[1]-1].x, md.obj_points[md.obj_faces[i].v[1]-1].y,md.obj_points[md.obj_faces[i].v[1]-1].z);
		glVertex3f(md.obj_points[md.obj_faces[i].v[2]-1].x, md.obj_points[md.obj_faces[i].v[2]-1].y,md.obj_points[md.obj_faces[i].v[2]-1].z);


	}

	glEnd();
	glPopMatrix();

}

void DisplayModel2(model md)
{

	glPushMatrix();
	glBegin(GL_TRIANGLES);

	for (int i = 0; i < md.faces; i++)
	{
	
		glColor3f(md.color_[i].r, md.color_[i].g, md.color_[i].b); 

		glNormal3f(md.obj_normals[md.obj_faces[i].vn[0]-1].x,md.obj_normals[md.obj_faces[i].vn[0]-1].y,md.obj_normals[md.obj_faces[i].vn[0]-1].z);
		glNormal3f(md.obj_normals[md.obj_faces[i].vn[1]-1].x,md.obj_normals[md.obj_faces[i].vn[1]-1].y,md.obj_normals[md.obj_faces[i].vn[1]-1].z);
		glNormal3f(md.obj_normals[md.obj_faces[i].vn[2]-1].x,md.obj_normals[md.obj_faces[i].vn[2]-1].y,md.obj_normals[md.obj_faces[i].vn[2]-1].z);
		
		glVertex3f(md.obj_points[md.obj_faces[i].v[0]-1].x, md.obj_points[md.obj_faces[i].v[0]-1].y,md.obj_points[md.obj_faces[i].v[0]-1].z);
		glVertex3f(md.obj_points[md.obj_faces[i].v[1]-1].x, md.obj_points[md.obj_faces[i].v[1]-1].y,md.obj_points[md.obj_faces[i].v[1]-1].z);
		glVertex3f(md.obj_points[md.obj_faces[i].v[2]-1].x, md.obj_points[md.obj_faces[i].v[2]-1].y,md.obj_points[md.obj_faces[i].v[2]-1].z);


	}

	glEnd();
	glPopMatrix();
}
void Setup()  
{ glEnable( GL_CULL_FACE );
   ReadFile(&md);
   ReadFile2(&car,"SL500");
   ReadFile2(&grass,"Grass_03");
   
   //cout<<car.faces+grass.faces*6+md.faces<<endl;

   glShadeModel( GL_SMOOTH );

   glEnable(GL_DEPTH_TEST);
   glDepthFunc( GL_LEQUAL );      
   glClearDepth(1.0); 		      


   //Set up light source
   GLfloat ambientLight[] = { 0.3, 0.3, 0.3, 1.0 };
   GLfloat diffuseLight[] = { 1, 1, 1, 1.0 };
   GLfloat lightPos[] = { -20.0, 20.0, 150.0, 0.0 };
  // GLfloat lightPos[] = { 0.0, 100.0, 350.0, 1.0 };

   glLightfv( GL_LIGHT0, GL_AMBIENT, ambientLight );
   glLightfv( GL_LIGHT0, GL_DIFFUSE, diffuseLight );
   glLightfv( GL_LIGHT0, GL_POSITION,lightPos );


   GLfloat specularLight[] = { 1.0, 1.0, 1.0, 1.0 };
 	glLightfv( GL_LIGHT0, GL_SPECULAR, specularLight);
	GLfloat specref[] = { 1.0, 1.0, 1.0, 1.0 };
	glMaterialfv(GL_FRONT,GL_SPECULAR,specref);
	glMateriali(GL_FRONT,GL_SHININESS,128);

	// polygon rendering mode and material properties
	glPolygonMode(GL_FRONT_AND_BACK,GL_FILL);
   
    glEnable(GL_COLOR_MATERIAL);
    glColorMaterial( GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE );
   
	glEnable( GL_LIGHTING );
	glEnable( GL_LIGHT0);



	// Black background
	glClearColor(0.0f,0.0f,0.0f,1.0f);
}

