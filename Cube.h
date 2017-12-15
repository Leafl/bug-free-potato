/* 
 * File:   Tetrahedron.h
 * Author: stuetzlec
 *
 * Created on September 27, 2015, 6:58 PM
 */


#include "Triangle.hpp"
#include "Shader.hpp"
#include "DrawableObject.h"
#include "Vertex.hpp"
#include <GL/glew.h>

using glm::vec3;
class Triangle;

class Cube: public DrawableObject
{
public:
    Cube();
    Cube(vec3, double,
	 vec3 fillColor = vec3(1.0f, 1.0f, 1.0f),
	 vec3 borderColor = vec3(0.0f, 0.0f, 0.0f));
    Cube(const Cube& orig);
    virtual ~Cube();

    // The draw function
    void draw(Shader*);

    //vec3 getEyeDirection(Camera*, int vertNum = 0 );
private:
    Triangle* triangles[12];
    Vertex* vertices[8];
    double size;

    // Colors
    vec3 fillColor;
    vec3 borderColor;

    // Set up the VBO and VAO
    GLuint VAO;
    GLuint VBO;
};

