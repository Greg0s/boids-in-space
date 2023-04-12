#include "camera.hpp"

Camera::Camera(glm::vec3 coords)
    : m_coords({0., 0., 0.})
{
    m_coords = coords;
}

void Camera::setDistance(float dist)
{
    m_distance = dist;
}

float Camera::getDistance()
{
    return m_distance;
}

void Camera::setHeight(float height)
{
    m_height = height;
}

float Camera::getHeight()
{
    return m_height;
}

void Camera::calCoords(glm::vec3 mainPos)
{
    glm::vec2 pos(mainPos - m_distance);
    m_coords = {pos, m_height};
}
