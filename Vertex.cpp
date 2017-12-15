#include "Vertex.hpp"

Vertex::Vertex(vec3 pos, vec3 col)
{
    position=pos;
    color=col;
    tex_coord=vec2(0.0f, 0.0f);
    normal=vec3(0.0f, 1.0f, 0.0f);
}


// This function adds a Triangle pointer to a triangle object

void Vertex::addTriangle(Triangle* t)
{
    triangles.push_back(t);
}

void Vertex::calculateNormal()
{
    // Average the normals of the neighboring triangles
    vec3 ave(0.0, 0.0, 0.0);
    for(int i=0; i<triangles.size(); i++)
    {
	ave+=triangles[i] -> getNormal();
    }
    ave/=triangles.size();
    glm::normalize(ave);
    normal=ave;
}