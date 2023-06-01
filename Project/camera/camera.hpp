#pragma once

#include "../player/player.hpp"
#include "p6/p6.h"

class Camera {
private:
    glm::vec3 m_coords   = {0.5, 0.25, 0.5};
    float     m_distance = 0.7;
    float     m_height   = 0.2;

public:
    void  setDistance(float dist);
    float getDistance() const;
    void  setHeight(float height);
    float getHeight();

    void further();
    void closer();

    void      calCoords(Player& player);
    glm::vec3 getCoords();
};