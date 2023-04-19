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

void Camera::calCoords(glm::vec3 playerPos)
{
    // glm::vec2 pos(mainPos.x - m_distance, );
    //  m_coords = {pos, m_height};
    m_coords = {playerPos.x - m_distance, m_height, playerPos.z};
}

glm::vec3 Camera::getCoords()
{
    return m_coords;
}
