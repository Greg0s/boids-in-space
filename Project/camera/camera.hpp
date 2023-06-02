#pragma once

#include "../player/player.hpp"
#include "p6/p6.h"

class Camera {
private:
    glm::vec3 m_coords   = {0.5, 0.25, 0.5};
    float     m_distance = 0.7;
    float     m_height   = 0.2;

public:
    float     getDistance() const { return m_distance; };
    float     getHeight() { return m_coords[2]; };
    glm::vec3 getCoords() { return m_coords; };

    void setDistance(float& dist);
    void setHeight(float& height);
    void calCoords(Player& player);

    void further();
    void closer();
};