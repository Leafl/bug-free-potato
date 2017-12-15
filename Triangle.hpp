/* 
 * File:   Triange.hpp
 * Author: stuetzlec
 *
 * Created on October 26, 2017, 2:59 PM
 */

#ifndef TRIANGLE_HPP
#define TRIANGLE_HPP

#include "Vertex.hpp"
#include <glm/glm.hpp>
#include <iostream>

using glm::vec3;

class Vertex;

class Triangle
{
public:
    Triangle(Vertex*, Vertex*, Vertex*);
    Triangle(const Triangle& orig);
    virtual ~Triangle();

    // Calculate the normal
    void calculateNormal();

    // Getters and Setters

    vec3 getNormal()
    {
	return normal;
    }

    Vertex* getV1()
    {
	return v1;
    }

    Vertex* getV2()
    {
	return v2;
    }

    Vertex* getV3()
    {
	return v3;
    }
private:
    Vertex* v1;
    Vertex* v2;
    Vertex* v3;

    vec3 normal;
};

#endif /* TRIANGE_HPP */

