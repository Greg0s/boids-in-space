#include "player.hpp"
#include "../loaderGLTF/Model.h"
#include "glm/gtx/transform.hpp"

float incrementUnit = 0.01;

glm::vec3 Player::getPos()
{
    return m_pos;
}

glm::vec3 Player::getDir()
{
    return m_dir;
}

void Player::goForward()
{
    m_pos.x += m_speed;
}

void Player::goBackward()
{
    m_pos.x -= m_speed;
}

void Player::goLeft()
{
    m_pos.z -= m_speed;
}

void Player::goRight()
{
    m_pos.z += m_speed;
}

void Player::goUp()
{
    m_pos.y += m_speed;
}

void Player::goDown()
{
    m_pos.y -= m_speed;
}

// void Player::rotateRight()
// {
//     m_dir.z += incrementUnit;
// }

// void Player::rotateLeft()
// {
//     m_dir.z -= incrementUnit;
// }

// void Player::move()
// {
//     m_pos = m_dir * m_speed;
// }

void Player::draw(const p6::Shader& shaderGLTF) const
{
    std::string fileGLTF = "./assets/models/drone.gltf";
    Model       player(fileGLTF.c_str());

    glm::mat4 base = glm::mat4(1.f);
    base           = glm::translate(base, glm::vec3(m_pos.x, m_pos.y, m_pos.z));

    base = glm::scale(base, glm::vec3(0.01));

    shaderGLTF.set("model", base);
    player.Draw(shaderGLTF.id());
}