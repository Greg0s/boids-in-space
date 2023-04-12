#pragma once

#include "p6/p6.h"

class Camera {
private:
    glm::vec3 m_coords;
    float     m_distance;
    float     m_height;

public:
    explicit Camera(glm::vec3 coords);

    void  setDistance(float dist);
    float getDistance();
    void  setHeight(float height);
    float getHeight();

    void calCoords(glm::vec3 mainPos);
};