/* 
 * File:   StandardRectangulaPrisim.cpp
 * Author: Suzuka
 * 
 * Date: December 12, 2017, 3:15 PM
 * 
 * heavily based upon
 * File:   StandardRectangulaPrisim.cpp
 * Author: stuetzlec
 * 
 * has been altered by Suzuka
 */

#include "StandardRectangulaPrisim.h"

StandardRectangulaPrisim::StandardRectangulaPrisim()
{
    assert(false&&"Do not use default StandardRectangulaPrisim constructor.");
}

StandardRectangulaPrisim::StandardRectangulaPrisim(vec3 _f, float _length, float _width, float _depth, vec3 fc, vec3 bC)
{
    fillColor=fc;
    borderColor=bC;
    length=_length;
    width=_width;
    depth=_depth;
    anchorPoint=_f;

    //f
    vertices[0]=new Vertex(_f, fillColor);
    vertices[0] -> setNormal(glm::normalize(vec3(-1, -1, -1)));

    //e
    vertices[1]=new Vertex(_f+vec3(length, 0.0, 0.0), fillColor);
    vertices[1] -> setNormal(glm::normalize(vec3(1, -1, -1)));

    //g
    vertices[2]=new Vertex(_f+vec3(length, depth, 0.0), fillColor);
    vertices[2] -> setNormal(glm::normalize(vec3(1, 1, -1)));

    //h
    vertices[3]=new Vertex(_f+vec3(0.0, depth, 0.0), fillColor);
    vertices[3] -> setNormal(glm::normalize(vec3(-1, 1, -1)));

    //b
    vertices[4]=new Vertex(_f+vec3(0.0, 0.0, width), fillColor);
    vertices[4] -> setNormal(glm::normalize(vec3(-1, -1, 1)));

    //c
    vertices[5]=new Vertex(_f+vec3(length, 0.0, width), fillColor);
    vertices[5] -> setNormal(glm::normalize(vec3(1, -1, 1)));

    //d
    vertices[6]=new Vertex(_f+vec3(length, depth, width), fillColor);
    vertices[6] -> setNormal(glm::normalize(vec3(1, 1, 1)));

    //a
    vertices[7]=new Vertex(_f+vec3(0.0, depth, width), fillColor);
    vertices[7] -> setNormal(glm::normalize(vec3(-1, 1, 1)));

    // Set up the triangles
    triangles[0]=new Triangle(vertices[0], vertices[1], vertices[2]);
    vertices[0]->addTriangle(triangles[0]);
    vertices[1]->addTriangle(triangles[0]);
    vertices[2]->addTriangle(triangles[0]);
    triangles[1]=new Triangle(vertices[0], vertices[2], vertices[3]);
    vertices[0]->addTriangle(triangles[1]);
    vertices[2]->addTriangle(triangles[1]);
    vertices[3]->addTriangle(triangles[1]);
    triangles[2]=new Triangle(vertices[0], vertices[5], vertices[1]);
    vertices[0]->addTriangle(triangles[2]);
    vertices[5]->addTriangle(triangles[2]);
    vertices[1]->addTriangle(triangles[2]);
    triangles[3]=new Triangle(vertices[0], vertices[4], vertices[5]);
    vertices[0]->addTriangle(triangles[3]);
    vertices[4]->addTriangle(triangles[3]);
    vertices[5]->addTriangle(triangles[3]);
    triangles[4]=new Triangle(vertices[0], vertices[3], vertices[4]);
    vertices[0]->addTriangle(triangles[4]);
    vertices[3]->addTriangle(triangles[4]);
    vertices[4]->addTriangle(triangles[4]);
    triangles[5]=new Triangle(vertices[7], vertices[4], vertices[3]);
    vertices[7]->addTriangle(triangles[5]);
    vertices[4]->addTriangle(triangles[5]);
    vertices[3]->addTriangle(triangles[5]);
    triangles[6]=new Triangle(vertices[1], vertices[6], vertices[2]);
    vertices[1]->addTriangle(triangles[6]);
    vertices[6]->addTriangle(triangles[6]);
    vertices[2]->addTriangle(triangles[6]);
    triangles[7]=new Triangle(vertices[1], vertices[5], vertices[6]);
    vertices[1]->addTriangle(triangles[7]);
    vertices[5]->addTriangle(triangles[7]);
    vertices[6]->addTriangle(triangles[7]);
    triangles[8]=new Triangle(vertices[2], vertices[6], vertices[3]);
    vertices[2]->addTriangle(triangles[8]);
    vertices[6]->addTriangle(triangles[8]);
    vertices[3]->addTriangle(triangles[8]);
    triangles[9]=new Triangle(vertices[3], vertices[6], vertices[7]);
    vertices[3]->addTriangle(triangles[9]);
    vertices[6]->addTriangle(triangles[9]);
    vertices[7]->addTriangle(triangles[9]);
    triangles[10]=new Triangle(vertices[7], vertices[6], vertices[4]);
    vertices[7]->addTriangle(triangles[10]);
    vertices[6]->addTriangle(triangles[10]);
    vertices[4]->addTriangle(triangles[10]);
    triangles[11]=new Triangle(vertices[4], vertices[6], vertices[5]);
    vertices[4]->addTriangle(triangles[11]);
    vertices[6]->addTriangle(triangles[11]);
    vertices[5]->addTriangle(triangles[11]);

    for(int i=0; i<12; i++)
    {
	triangles[i] -> calculateNormal();
    }
    /*
    // Average the color and the normal for the neighboring triangles
    for (int i = 0; i < 8; i++) {
	vertices[i] -> calculateNormal();
    }*/

    // Build a verts (and others) array for OpenGL
    GLfloat verts[108];
    GLfloat colors[108];
    GLfloat normals[108];
    int index;
    for(int v=0; v<108;)
    {
	index=v/9;
	verts[v++]=triangles[index]->getV1()->getPos().x;
	verts[v++]=triangles[index]->getV1()->getPos().y;
	verts[v++]=triangles[index]->getV1()->getPos().z;
	verts[v++]=triangles[index]->getV2()->getPos().x;
	verts[v++]=triangles[index]->getV2()->getPos().y;
	verts[v++]=triangles[index]->getV2()->getPos().z;
	verts[v++]=triangles[index]->getV3()->getPos().x;
	verts[v++]=triangles[index]->getV3()->getPos().y;
	verts[v++]=triangles[index]->getV3()->getPos().z;
    }
    for(int v=0; v<108;)
    {
	index=v/9;
	colors[v++]=triangles[index]->getV1()->getColor().r;
	colors[v++]=triangles[index]->getV1()->getColor().g;
	colors[v++]=triangles[index]->getV1()->getColor().b;
	colors[v++]=triangles[index]->getV2()->getColor().r;
	colors[v++]=triangles[index]->getV2()->getColor().g;
	colors[v++]=triangles[index]->getV2()->getColor().b;
	colors[v++]=triangles[index]->getV3()->getColor().r;
	colors[v++]=triangles[index]->getV3()->getColor().g;
	colors[v++]=triangles[index]->getV3()->getColor().b;
    }
    for(int v=0; v<108;)
    {
	index=v/9;
	normals[v++]=triangles[index]->getV1()->getNormal().x;
	normals[v++]=triangles[index]->getV1()->getNormal().y;
	normals[v++]=triangles[index]->getV1()->getNormal().z;
	normals[v++]=triangles[index]->getV2()->getNormal().x;
	normals[v++]=triangles[index]->getV2()->getNormal().y;
	normals[v++]=triangles[index]->getV2()->getNormal().z;
	normals[v++]=triangles[index]->getV3()->getNormal().x;
	normals[v++]=triangles[index]->getV3()->getNormal().y;
	normals[v++]=triangles[index]->getV3()->getNormal().z;
    }

    // Set up standardRectangularPrisim_VertexBufferObject and standardRectangularPrisim_VertexArrayObject
    // Set up the standardRectangularPrisim_VertexBufferObject
    glGenVertexArrays(1, &standardRectangularPrisim_VertexArrayObject);
    glGenBuffers(1, &standardRectangularPrisim_VertexBufferObject);
    glBindVertexArray(standardRectangularPrisim_VertexArrayObject);
    glBindBuffer(GL_ARRAY_BUFFER, standardRectangularPrisim_VertexBufferObject);

    // Populate with the data
    glBufferData(GL_ARRAY_BUFFER,
		 sizeof(verts)+sizeof(colors)+sizeof(normals), NULL, GL_STATIC_DRAW);
    glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(verts), &verts[0]);
    glBufferSubData(GL_ARRAY_BUFFER, sizeof(verts), sizeof(colors), &colors[0]);
    glBufferSubData(GL_ARRAY_BUFFER, sizeof(verts)+sizeof(colors),
		    sizeof(normals), &normals[0]);

    // Set up the attribute array with two attributes
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, (void*) sizeof(verts));
    glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 0, (void*) (sizeof(verts)+sizeof(colors)));
    glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(1);
    glEnableVertexAttribArray(2);
}

// Copy constructor is UNDER CONSTRUCTION (get it?!)

StandardRectangulaPrisim::StandardRectangulaPrisim(const StandardRectangulaPrisim& orig){ }

StandardRectangulaPrisim::~StandardRectangulaPrisim(){
    // Delete triangles

    // Delete vertices
}

// The drawing function
// Pre: None
// Post: The tetrahedron is drawn to the screen

void StandardRectangulaPrisim::draw(Shader* s)
{
    glBindVertexArray(standardRectangularPrisim_VertexBufferObject);
    s->useProgram();
    glDrawArrays(GL_TRIANGLES, 0, 36);
    glBindVertexArray(0);
}

/*
vec3 StandardRectangulaPrisim::getEyeDirection( Camera* c, int vertNum ) {
    assert( vertNum < 8 && vertNum >= 0 );
    return glm::normalize(c->getPosition() - vertices[vertNum]->getPos());
}
 * */
