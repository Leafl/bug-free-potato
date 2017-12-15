/* 
 * File:   StandardRectangulaPrisim.h
 * Author: Suzuka
 *
 * Date: December 12, 2017, 3:15 PM
 * 
 * Based heavily upon: 
 * File:   Cube.h
 * Author: stuetzlec
 *
 */
#ifndef STANDARDRECTANGULAPRISIM_H
#define STANDARDRECTANGULAPRISIM_H

#include "Triangle.hpp"
#include "Shader.hpp"
#include "DrawableObject.h"
#include "Vertex.hpp"
#include <GL/glew.h>

using glm::vec3;
class Triangle;

class StandardRectangulaPrisim: public DrawableObject
{
public:
    StandardRectangulaPrisim();
    StandardRectangulaPrisim(vec3 _f, float leng, float widt, float depth, vec3 fillColor, vec3 borderColor);
    StandardRectangulaPrisim(const StandardRectangulaPrisim& orig);
    virtual ~StandardRectangulaPrisim();

    // The draw function
    void draw(Shader*);

    //vec3 getEyeDirection(Camera*, int vertNum = 0 );
private:
    /* Position Points */
    vec3 anchorPoint;//furthest back left conner of the standared rectangular prisim
    float depth;
    float length;
    float width;

    Triangle* triangles[12];
    Vertex* vertices[8];

    // Colors
    vec3 fillColor = vec3(1.0f, 1.0f, 1.0f);
    vec3 borderColor = vec3(0.0f, 0.0f, 0.0f);

    // Set up the VBO and VAO
    GLuint standardRectangularPrisim_VertexArrayObject;
    GLuint standardRectangularPrisim_VertexBufferObject;
};
#endif /* STANDARDRECTANGULAPRISIM_H */