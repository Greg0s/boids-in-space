#include "player.hpp"

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
    m_pos.x += m_dir.x;
}

void Player::goBackward()
{
    m_pos.x -= m_dir.x;
}

void Player::goLeft()
{
    m_pos.z -= m_dir.z;
}

void Player::goRight()
{
    m_pos.z += m_dir.z;
}