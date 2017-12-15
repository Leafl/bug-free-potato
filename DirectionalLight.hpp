/*
 * File:   DirectionalLight.hpp
 * Author: stuetzlec
 *
 * Created on October 27, 2017, 1:34 PM
 */

#ifndef DIRECTIONALLIGHT_HPP
#define DIRECTIONALLIGHT_HPP

#include "Light.hpp"
#include <glm/glm.hpp>

using glm::vec3;

class DirectionalLight: public Light
{
public:
    DirectionalLight(vec3 col, vec3 dir, GLfloat strength, GLfloat shine);
    DirectionalLight(const DirectionalLight& orig);
    virtual ~DirectionalLight();

    void connectLightToShader(Shader*);
private:
    vec3 direction;

    GLfloat shininess;
    GLfloat strength;
};

#endif /* DIRECTIONALLIGHT_HPP */

