#include "glm/fwd.hpp"
#include "p6/p6.h"

#pragma once

class Player {
private:
    glm::vec3 m_pos = {0., 0., 0.};
    glm::vec3 m_dir = {0.01, 0.01, 0.01};

public:
    glm::vec3 getPos();
    glm::vec3 getDir();

    void goForward();
    void goBackward();
    void goLeft();
    void goRight();
};