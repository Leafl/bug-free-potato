#include "Light.hpp"

Light::Light(vec3 col)
{
    enabled=false;
    color=glm::normalize(col);
}