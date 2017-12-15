/* 
 * File:   DirectionalLight.cpp
 * Author: stuetzlec
 * 
 * Created on October 27, 2017, 1:34 PM
 */

#include "DirectionalLight.hpp"

DirectionalLight::DirectionalLight(vec3 col, vec3 dir, GLfloat st, GLfloat sh) :
 Light(col)
{
    direction=glm::normalize(dir);
    strength=st;
    shininess=sh;
}

DirectionalLight::DirectionalLight(const DirectionalLight& orig) : Light(orig){ }

DirectionalLight::~DirectionalLight(){ }

void DirectionalLight::connectLightToShader(Shader* s)
{
    // Connect to the variables
    GLint dirLightid=s->GetVariable("directLightColor");
    GLint shininessid=s->GetVariable("Shininess");
    GLint strengthid=s->GetVariable("Strength");
    GLint dirLightWeight=s->GetVariable("directionalWeight");
    GLint lightDirid=s->GetVariable("LightDirection");

    s->SetVector3(dirLightid, 1, &color[0]);
    s->SetVector3(lightDirid, 1, &direction[0]);
    s->SetFloat(shininessid, shininess);
    s->SetFloat(strengthid, strength);
    if(isEnabled()==true)
    {
	s->SetFloat(dirLightWeight, 1.0);//set directional weight to X
    }
    else if (isEnabled()==false)
    {
	s->SetFloat(dirLightWeight, 0.0);//set directional weight to 0
    }
}
