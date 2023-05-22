#pragma once

#include "glm/fwd.hpp"
#include "p6/p6.h"

class Player {
private:
    glm::vec3 m_pos = {0.f, 0.01, 0.f};
    glm::vec3 m_dir = {0.f, 0.f, 0.f};

    float m_rot = 0;

    float m_speed = 0.04;

public:
    glm::vec3
              getPos() const;
    glm::vec3 getDir() const;
    float     getRot() const;

    void goForward();
    void goBackward();
    void goLeft();
    void goRight();
    void goUp();
    void goDown();
    void rotateRight();
    void rotateLeft();

    void move();

    void calcDir();

    void draw(const p6::Shader& shaderGLTF) const;
};