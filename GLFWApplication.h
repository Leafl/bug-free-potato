/* 
 * File:   GLFWApplication.h
 * Author: stuetzlec
 *
 * Created on October 10, 2017, 3:31 PM
 */

#ifndef GLFWAPPLICATION_H
#define GLFWAPPLICATION_H

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#define GLM_FORCE_RADIANS       // Necessary because GLM reasons
#include <glm/glm.hpp>
#include <vector>
#include "Shader.hpp"
#include "Camera.h"
#include "Light.hpp"

#include "DrawableObject.h"

using glm::vec3;
using glm::vec2;
using glm::mat4;
using std::vector;

class GLFWApplication {
public:
    GLFWApplication();
    GLFWApplication(const GLFWApplication& orig);
    virtual ~GLFWApplication();

    // General Initialization Function
    int initializeApplication(int, int, int, string, int, int, vec3 cC = vec3(0.0, 0.0, 0.0));
    void initiateDrawLoop();

    // Add objects to the internal lists
    void addDrawableObject(DrawableObject*);
    void addLight( Light* );
    void setShaderProgram(Shader*); // Set the current shader program

    // Functions to set up the callbacks
    bool setKeyCallback(void (*func)(GLFWwindow*, int, int, int, int)) {
        keyFunc = func;
    }

    bool setMouseClickCallback(void (*func)(GLFWwindow*, int, int, int)) {
        clickFunc = func;
    }

    bool setMouseMotionCallback(void (*func)(GLFWwindow*, double, double)) {
        mouseMoveFunc = func;
    }
    void initializeCallbacks();

    // Set the camera and the shader

    void setCamera(Camera* c) {
        camera = c;
    }

    void setShader(Shader* s) {
        shader = s;
    }
    
    
    void setwalkingforward(bool set)
    {
		walkingforward = set;
    }

    void setwalkingbackward(bool set)
    {
		walkingbackward = set;
    }

    void setwalkingright(bool set)
    {
		walkingright = set;
    }

    void setwalkingleft(bool set)
    {
		walkingleft = set;
    }

    void setheadup(bool set)
    {
		headup = set;
    }

    void setheaddown(bool set)
    {
		headdown = set;
    }

    void setheadright(bool set)
    {
		headright = set;
    }

    void setheadleft(bool set)
    {
		headleft = set;
    }
private:
    const vec3 skyblue = vec3(0.196078, 0.6, 0.8);
    const vec3 lightpurple =vec3(0.87, 0.58, 0.98);

    vector< DrawableObject* > drawables; // The list of everything to draw
    vector< Light* > lights;
    double curTime; // The current time in the system
    Shader* shader; // The current shader program
    Camera* camera;
    GLFWwindow* window; // The OpenGL context window

    void draw(); // Draw all of the drawable objects

    // Callback functions using some function pointers
    void (*keyFunc)(GLFWwindow*, int, int, int, int);
    void (*clickFunc)(GLFWwindow*, int, int, int);
    void (*mouseMoveFunc)(GLFWwindow*, double, double);
    
    //bools for moving
    bool walkingforward;
    bool walkingbackward;
    bool walkingright;
    bool walkingleft;
    bool headup;
    bool headdown;
    bool headright;
    bool headleft;

};

#endif /* GLFWAPPLICATION_H */

