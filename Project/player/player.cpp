#include "player.hpp"

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
    m_pos.x += incrementUnit;
}

void Player::goBackward()
{
    m_pos.x -= incrementUnit;
}

void Player::goLeft()
{
    m_pos.z -= incrementUnit;
}

void Player::goRight()
{
    m_pos.z += incrementUnit;
}

// void Player::rotateRight()
// {
//     m_dir.z += incrementUnit;
// }

// void Player::rotateLeft()
// {
//     m_dir.z -= incrementUnit;
// }