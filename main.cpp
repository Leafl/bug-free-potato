
/* 
 * File:   main.cpp
 * Author: Suzuka
 *
 * retrieved from: CSC5210_Unit7_LightingExample.zip
 * Date: December 12, 2017, 3:05 PM
 */

#include <iostream>
#include <cstdio>

// User Includes
#define GLM_FORCE_RADIANS       // Necessary because GLM reasons
#include "StandardRectangulaPrisim.h"
#include "DirectionalLight.hpp"
#include "GLFWApplication.h"
#include "AmbientLight.hpp"
#include "Shader.hpp"
#include "Camera.h"
#include "Cube.h"


using std::endl;
using std::cerr;

// Window information
GLuint winHeight=1000;
GLuint winWidth=1000;

// The current mouse position
double deltaX, deltaY;
bool lButtonDown;
bool rButtonDown;
vec2 mousePos;

//Models
StandardRectangulaPrisim* surface;
StandardRectangulaPrisim* rectPrisim;
Cube* cube1;
Cube* c2;

Shader* currentShaders;

//Camera
Camera* camera;

// Lights
Light* ambLight;
Light* dirLight;

vec3 ambientLightColor = vec3 (0.5, 0.3, 0.9999);

//surface stuff
const float LENGTH=240; //X
const float WIDTH=240; //Z
const float DEPTH=10.0f; //Y
const vec3 SURFACE_POS=vec3(-1*(LENGTH/2), -1*DEPTH, -1*(WIDTH/2));

vec3 red=vec3(1.0f, 0.1f, 0.1f); // Reddish
vec3 blue=vec3(0.1f, 0.1f, 1.f); // Blueish
vec3 white=vec3(1, 1, 1);
vec3 black=vec3(0, 0, 0);
vec3 seaGreen=vec3(0.137255f, 0.556863f, 0.419608f);
vec3 limegreen = vec3(0.81, 0.71, 0.23);


GLFWApplication hippoApplication;

string searchPath="/Volumes/NO NAME/Personal OpenGL stuff/MockLighting/MockLighting/";


void init()
{
    

    // Create a tetrahedron in back
    cube1=new Cube(vec3(-2, 0.0, 5.0), // The four corners
		5.0, // The size of one edge of the cube
		red, // The fill color
		black // The border color
		);
    surface=new StandardRectangulaPrisim(SURFACE_POS, LENGTH, WIDTH, DEPTH, seaGreen, black);

    //red 0.81 green 0.71 blue 0.23
    rectPrisim=new StandardRectangulaPrisim(vec3(0.0, 0.0, 10), 5.0, 2, 4,white,blue);

    // Finally, tell the application object about the drawable objects
    hippoApplication.addDrawableObject(cube1);
    hippoApplication.addDrawableObject(rectPrisim);
    hippoApplication.addDrawableObject(surface);
    
    // Set up the lights
    ambLight=new AmbientLight(ambientLightColor);
    ambLight -> enable();
    dirLight=new DirectionalLight(vec3(0.9, 0.2, 0.2),
				  glm::normalize(vec3(-1.0, 1.0, 1.0)), 0.8, 0.51);
    //dirLight -> enable();
    hippoApplication.addLight(ambLight);
    hippoApplication.addLight(dirLight);


    // Set up the shader
    string shaders[]=
    {
	searchPath+"vertices.vert",
	searchPath+"fragments.frag"
    };
    currentShaders=new Shader(shaders, true);

    // Set up the camera
    vec3 pos(1, 5, 20);
    GLfloat FOV=45.0f;
    GLfloat nearPlane=0.1f;
    GLfloat farPlane=1000.0f;
    camera=new Camera(pos, winWidth, winHeight);
    camera -> setPerspective(FOV, (GLfloat) winWidth/(GLfloat) winHeight, nearPlane, farPlane);
}

// Update the mouse position (and the change in the position from the
//   previous update) in here.

void mouse_motion_callback(GLFWwindow* window, double mX, double mY)
{
    deltaX=mousePos.x-mX;
    deltaY=mousePos.y-mY;
    mousePos.x=mX;
    mousePos.y=mY;

    // If the associated button is down, make sure to update the camera accordingly.
    if(lButtonDown)
    {
	camera -> setViewByMouse(deltaX, deltaY);
    }
}

// When a mouse button is clicked, change the state of the "left" and "right"
//   buttons to being held down (when pressed) or not (when released).

void mouse_callback(GLFWwindow* window, int button, int action, int mods)
{
    if(button==GLFW_MOUSE_BUTTON_LEFT)
    {
	if(GLFW_PRESS==action)
	    lButtonDown=true;
	else if(GLFW_RELEASE==action)
	    lButtonDown=false;
    }
    else if(button==GLFW_MOUSE_BUTTON_RIGHT)
    {
	if(GLFW_PRESS==action)
	    rButtonDown=true;
	else if(GLFW_RELEASE==action)
	    rButtonDown=false;
    }
}

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode)
{
    // Only trigger upon release
    if(action==GLFW_PRESS)
    {
	if(key==GLFW_KEY_Q||key==GLFW_KEY_ESCAPE)
	{
	    glfwSetWindowShouldClose(window, GL_TRUE);
	}
	if(key==GLFW_KEY_W)
            {
                hippoApplication.setwalkingforward(true);
            }
            if(key==GLFW_KEY_S)
            {
                hippoApplication.setwalkingbackward(true);
            }
            if(key==GLFW_KEY_A)
            {
                hippoApplication.setwalkingleft(true);
            }
            if(key==GLFW_KEY_D)
            {
                hippoApplication.setwalkingright(true);
            }
            if (key == GLFW_KEY_DOWN)
            {
                hippoApplication.setheaddown(true);
            }
            if (key == GLFW_KEY_UP)
            {
                hippoApplication.setheadup(true);
            }
            if (key == GLFW_KEY_LEFT)
            {
                hippoApplication.setheadleft(true);
            }
            if (key == GLFW_KEY_RIGHT)
            {
                hippoApplication.setheadright(true);
            }
	
            if(key==GLFW_KEY_MINUS)
	    {
		    ((AmbientLight*) ambLight)->raiseWeight();
	    }
	    else if (key==GLFW_KEY_EQUAL)
	    {
		    ((AmbientLight*) ambLight)->lowerWeight();
	    }
    }
    else if (action==GLFW_RELEASE)
    {
	if (key == GLFW_KEY_W)
        {
            hippoApplication.setwalkingforward(false);
        }
        if (key == GLFW_KEY_S)
        {
            hippoApplication.setwalkingbackward(false);
        }
        if (key == GLFW_KEY_A)
        {
            hippoApplication.setwalkingleft(false);
        }
        if (key == GLFW_KEY_D)
        {
            hippoApplication.setwalkingright(false);
        }
        if (key == GLFW_KEY_DOWN)
        {
            hippoApplication.setheaddown(false);
        }
        if (key == GLFW_KEY_UP)
        {
            hippoApplication.setheadup(false);
        }
        if (key == GLFW_KEY_LEFT)
        {
            hippoApplication.setheadleft(false);
        }
        if (key == GLFW_KEY_RIGHT)
        {
            hippoApplication.setheadright(false);
        }
	
        if(key==GLFW_KEY_R)
	{
		// add 10 degree rotation about the Z axis
		rectPrisim -> applyTransformation(glm::rotate(glm::mat4(1.0f), glm::radians(10.0f), glm::normalize(glm::vec3(1.0, 1.0, 1.0))));
	}
	if(key==GLFW_KEY_I)
	{
		ambLight -> toggle();
	}
	if(key==GLFW_KEY_O)
	{
		dirLight -> toggle();
	}
	
	if (key==GLFW_KEY_RIGHT_BRACKET)
	{
		((AmbientLight*) ambLight)->printAmbientLightweight();
	}


    }
}

int main()
{
    // Set up the GLFW application
    hippoApplication.initializeApplication(8, 3, 3,
					   "Lighting Example", winWidth, winHeight);

    // Assign your callback functions (the ones you write) to the internal
    //   callbacks of the application class.
    hippoApplication.setKeyCallback(key_callback);
    hippoApplication.setMouseClickCallback(mouse_callback);
    hippoApplication.setMouseMotionCallback(mouse_motion_callback);
    hippoApplication.initializeCallbacks();

    // Initialize stuff local to the program
    init();
    hippoApplication.setShader(currentShaders);
    hippoApplication.setCamera(camera);

    // Tell the application to "go"
    hippoApplication.initiateDrawLoop();

    return 0;
}

