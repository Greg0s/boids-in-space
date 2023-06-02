#include "camera.hpp"
#include "glm/fwd.hpp"

void Camera::setDistance(float& dist)
{
    m_distance = dist;
}

void Camera::setHeight(float& height)
{
    m_coords[2] = height;
}

void Camera::further()
{
    if (m_distance < 2)
        m_distance += 0.025;
}

void Camera::closer()
{
    if (m_distance > 0.5)
        m_distance -= 0.025;
}

void Camera::calCoords(Player& player)
{
    m_coords.y = player.getPos().y + m_height;
    m_coords.x = player.getPos().x + m_distance * glm::cos(player.getRot() - p6::PI);
    m_coords.z = player.getPos().z + m_distance * glm::sin(player.getRot() - p6::PI);
}