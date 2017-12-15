#ifndef _Camera_H
#define _Camera_H
#include <GL/glew.h>
#include <cmath>
#include <vector>
#include <fstream>
#include <iostream>
#include <glm/glm.hpp>                  // Used for the GLM math library
#include <glm/gtc/matrix_transform.hpp>	// Used for the GLM math library
#include <cmath>

using std::cerr;
using std::endl;
using namespace glm;

// A value for PI
const float PI = acos(-1.0);

// This is our Camera class to manage user movement in our 3D scene

class Camera
{
public:

    enum Camera_Movement
    {
	FORWARD,
	BACKWARD,
	LEFT,
	RIGHT
    };
    
    Camera();
    Camera(vec3 pos, float windowWidth, float windowHeight);

    // Functions to get and set the view and projection matrices based on camera
    mat4 getViewMatrix();
    mat4 getPerspectiveMatrix();
    mat4 getOrthographicMatrix();
    void setPerspective(float, float, float, float);
    
    //print functions
    void printAllInfo();
    void printOutYawandPitch();

    // setters
    void setPosition(vec3);
    void setPosition(float, float, float);
    void setDeltaTime(double);
    void setViewByMouse(float, float);
    
    //getters
    vec3 getPosition();
    vec3 getFront();
    vec3 getViewVector();
    vec3 getRightVector();
    vec3 calculateUpVector();
    float getMouseSpeed();
    
    // This function changes the view
    //   based on the delta of the mouse 
    //   coordinates
    
    void processMovement(Camera_Movement direction, GLboolean constrainVerticalHeight = true);
    void processHeadMovement(float xoffset, float yoffset, GLboolean constrainPitch);
    
    void moveCamera(float, float);
    void zoomCamera(float);
    


protected:
	mat4 ProjectionMatrix;// The camera's projection matrix
	vec3 cameraPosition;// The camera's position
	vec3 front_vector;
	vec3 up_vector;
	vec3 right_vector;
	vec3 worldup;
	
	float verticalheight;//added by emma

    float FOV;
    float AspectRatio;
    float nearPlane;
    float farPlane;

    // The size of the screen is needed 
    float ScreenWidth;
    float ScreenHeight;

    double deltaTime; // The time between frames
    float Speed; // The camera's speed that is used with a time slice
    float RotationSpeed; // The rotation speed for the mouse wheel
    double MouseSpeed; // The speed for the mouse rotations
    float yaw; // The horizontal rotation angle (in radians), y-axis
    float pitch; // The vertical rotation angle (in radians, x-axis
    float MovementSpeed;
    
    
    void updateCameraVectors();

    // Added by Chris Stuetzle
    void setDefaults();
};

#endif 
