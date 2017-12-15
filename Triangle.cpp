/* 
 * File:   Triange.cpp
 * Author: stuetzlec
 * 
 * Created on October 26, 2017, 2:59 PM
 */

#include "Triangle.hpp"

Triangle::Triangle(Vertex* _v1, Vertex* _v2, Vertex* _v3)
{
    v1=_v1;
    v2=_v2;
    v3=_v3;
}

Triangle::Triangle(const Triangle& orig)
{
    assert(false&&"No!");
}

Triangle::~Triangle(){ }

// To calculate the normal, get the cross product

void Triangle::calculateNormal()
{
    vec3 AB=v1->getPos()-v2->getPos();
    vec3 BC=v3->getPos()-v1->getPos();
    normal=glm::cross(AB, BC);
    normal=glm::normalize(normal);
}

