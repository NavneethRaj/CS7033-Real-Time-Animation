
//-------- Functions --------------------------------

void Render();
// The function responsible for drawing everything in the 
// OpenGL context associated to a window. 

void Resize(int w, int h);
// Handle the window size changes and define the world coordinate 
// system and projection type

void Setup();
// Set up the OpenGL state machine and create a light source

void Idle();

void Keyboard(unsigned char key,int x,int y);
// Function for handling keyboard events.

void special(int key, int x, int y);
// Function for arrows because Keyboard is for ASCII

void Mouse(int button,int state,int x,int y); 
// Function for handling mouse events

void Motion(int x, int y);


void keimeno(const char *str,float size,float off);
void keimeno2(const char *str,float size);

//down ehre for the .obj
struct point 
{
	float x; 
	float y; 
	float z; 
};

struct face
{
	int v[3];
	int vn[3];
};
struct normal
{
	float x;
	float y;
	float z;
};

struct col	//gia to fortoma tou xromatos tou amaksiou .obj
{
	float r;
	float g;
	float b;
};
struct model
{   
	col *color_;
	point *obj_points;
	face *obj_faces;
	normal *obj_normals;
	int vertices;
	int faces;
	int normals;
};

void ReadFile(model*);
//Function for reading a model file(dentro)

//void ReadFile2(model *md,string);
//Function for reading a model file(car)

void DisplayModel(model);
// Function for displaying a model tree

void DisplayModel2(model md);
// Function for displaying a model car