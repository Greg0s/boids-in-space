#include "player.hpp"
#include "../loaderGLTF/Model.h"
#include "glm/gtx/transform.hpp"

const float rotUnit      = p6::PI / 24;
const float maxSpeed     = 0.06;
const float minSpeed     = 0.04;
const float acceleration = 0.001;

glm::vec3 Player::getPos() const
{
    return m_pos;
}

glm::vec3 Player::getDir() const
{
    return m_dir;
}

float Player::getRot() const
{
    return m_rot;
}

void Player::goForward()
{
    // if (m_speed + acceleration < maxSpeed)
    //     m_speed += acceleration;
    m_pos.x += m_speed * m_dir.x;
    m_pos.z += m_speed * m_dir.z;
    // std::cout << m_dir.x << " et " << m_dir.z << std::endl;
}

void Player::goBackward()
{
    // if (m_speed - acceleration > minSpeed)
    //     m_speed -= acceleration;

    m_pos.x -= m_speed * m_dir.x;
    m_pos.z -= m_speed * m_dir.z;
}

// void Player::goLeft()
// {
//     m_pos.z -= m_speed;
// }

// void Player::goRight()
// {
//     m_pos.z += m_speed;
// }

void Player::goUp()
{
    m_pos.y += m_speed;
}

void Player::goDown()
{
    m_pos.y -= m_speed;
}

// only change sight direction
void Player::rotateRight()
{
    m_rot += rotUnit;
    // while (m_rot < 0)
    // {
    //     m_rot += 2 * p6::PI;
    // }
    // while (m_rot > 2 * p6::PI)
    // {
    //     m_rot -= 2 * p6::PI;
    // }
}

// only change sight direction
void Player::rotateLeft()
{
    m_rot -= rotUnit;
}

void Player::move()
{
    m_pos = m_dir * m_speed;
}

void Player::calcDir()
{
    // m_dir = glm::vec3(glm::cos(m_rot), glm::sin(m_rot), glm::sin(m_rot));
    m_dir.x = glm::cos(m_rot);
    m_dir.z = glm::sin(m_rot);
    // m_dir.x = x + distanceToPlayer * glm::cos(glm::radians(player.getRot() - 180));
}

void Player::draw(const p6::Shader& shaderGLTF) const
{
    std::string fileGLTF = "./assets/models/drone.gltf";
    Model       player(fileGLTF.c_str());

    glm::mat4 base = glm::mat4(1.f);

    base = glm::translate(base, glm::vec3(m_pos.x, m_pos.y, m_pos.z));
    // base = glm::rotate(base, p6::PI, glm::vec3(0.0f, 1.0f, 0.0f));
    base = glm::rotate(base, -m_rot, glm::vec3(0.0f, 1.0f, 0.0f));

    base = glm::scale(base, glm::vec3(0.01));

    shaderGLTF.set("model", base);
    player.Draw(shaderGLTF.id());
    std::cout << m_pos.x << "et" << m_pos.z << std::endl;
    std::cout << m_rot << std::endl;
}