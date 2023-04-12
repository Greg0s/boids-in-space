#pragma once

#include "p6/p6.h"

class Camera {
private:
    glm::vec3 m_coords   = {0.5, 0.25, 0.5};
    float     m_distance = 0.3;
    // float     m_height   = 0.5;

public:
    void  setDistance(float dist);
    float getDistance();
    void  setHeight(float height);
    float getHeight();

    void      calCoords(glm::vec3 mainPos);
    glm::vec3 getCoords();
};