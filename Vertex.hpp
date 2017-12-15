#ifndef VERTEX_HPP
#define VERTEX_HPP

#include <vector>
#include <glm/glm.hpp>
#include "Triangle.hpp"
#include <iostream>

using std::vector;
using glm::vec3;
using glm::vec2;
using std::cerr;
using std::endl;

class Triangle;

class Vertex
{
public:
    Vertex(vec3 pos, vec3 col);

    // Add a triangle to the list
    void addTriangle(Triangle*);
    void calculateNormal();

    // Getters, Setters

    vec3 getPos()
    {
	return position;
    }

    vec3 getColor()
    {
	return color;
    }

    vec3 getNormal()
    {
	return normal;
    }

    void setNormal(vec3 n)
    {
	normal = n;
    }
private:
    vector<Triangle*> triangles;

    vec3 position;
    vec3 color;
    vec3 normal;
    vec2 tex_coord;
};



#endif