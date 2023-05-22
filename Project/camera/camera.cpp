#include "camera.hpp"
#include "glm/fwd.hpp"

void Camera::setDistance(float dist)
{
    m_distance = dist;
}

float Camera::getDistance() const
{
    return m_distance;
}

void Camera::setHeight(float height)
{
    m_coords[2] = height;
}

float Camera::getHeight()
{
    return m_coords[2];
}

void Camera::calCoords(Player& player)
{
    // glm::vec2 pos(mainPos.x - m_distance, );
    //  m_coords = {pos, m_height};
    float distanceToPlayer = 0.5;

    m_coords.y = player.getPos().y + m_height;
    m_coords.x = player.getPos().x + distanceToPlayer * glm::cos(player.getRot() - p6::PI);
    m_coords.z = player.getPos().z + distanceToPlayer * glm::sin(player.getRot() - p6::PI);
}

glm::vec3 Camera::getCoords()
{
    return m_coords;
}
