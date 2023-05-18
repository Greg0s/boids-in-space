#include "glm/fwd.hpp"
#include "p6/p6.h"

#pragma once

class Player {
private:
    glm::vec3 m_pos = {0., 0., 0.};
    glm::vec3 m_dir = {1.f, 1.f, 1.f};

    float m_speed = 0.01;

public:
    glm::vec3 getPos();
    glm::vec3 getDir();

    void goForward();
    void goBackward();
    void goLeft();
    void goRight();
    void goUp();
    void goDown();
    // void rotateRight();
    // void rotateLeft();

    // void move();

    void draw(const p6::Shader& shaderGLTF) const;
};