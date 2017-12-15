/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   AmbientLight.h
 * Author: stuetzlec
 *
 * Created on October 27, 2017, 1:30 PM
 */

#ifndef AMBIENTLIGHT_H
#define AMBIENTLIGHT_H

#include <glm/glm.hpp>
#include "Light.hpp"

using glm::vec3;
using std::min;
using std::max;

class AmbientLight: public Light
{
public:
    AmbientLight(vec3 color);
    AmbientLight(const AmbientLight& orig);
    virtual ~AmbientLight();

    void connectLightToShader(Shader*);
    
    void printAmbientLightweight()
    {
    	printf("Current ambient light weight: %10f\n\n", weight);
    }

    void raiseWeight()
    {
	weight = std::min (weight + 0.1, 1.0);
    }

    void lowerWeight()
    {
	weight = std::max (weight - 0.1, 1.0);
    }
    
    void setWeight(float newWeight)
    {
    	if (newWeight >= 1.0f)
    	{
	    weight= std::min(newWeight,1.0f);
	}
	else if (newWeight<= 0.1)
	{
	    weight = std::max(newWeight,0.1f);
	}
    }
private:
    float weight = 0.2;
};

#endif /* AMBIENTLIGHT_H */

