#pragma once

#include "../loaderGLTF/Model.h"
#include "../loaderGLTF/gltf.hpp"
#include "glm/fwd.hpp"
#include "p6/p6.h"

class Player {
private:
    glm::vec3 m_pos;
    glm::vec3 m_dir;

    float m_rot;

    float m_speed;

    Gltf m_gltf;

public:
    Player(std::string fileGLTF);
    void init();

    glm::vec3 getPos() const;
    glm::vec3 getDir() const;
    float     getRot() const;

    void goForward(const p6::Context& ctx);
    void goBackward(const p6::Context& ctx);
    void goLeft();
    void goRight();
    void goUp(const p6::Context& ctx);
    void goDown(const p6::Context& ctx);
    void rotateRight(const p6::Context& ctx);
    void rotateLeft(const p6::Context& ctx);
    void brake(const p6::Context& ctx);

    void move();

    void calcDir();

    void draw(const p6::Shader& shaderGLTF);
};