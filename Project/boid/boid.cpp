#include "./boid.hpp"
#include "glm/ext/matrix_transform.hpp"
#include "glm/ext/quaternion_geometric.hpp"
#include "glm/fwd.hpp"

glm::vec3 Boid::getPosition() const
{
    return m_pos;
}

glm::vec3 Boid::getDirection() const
{
    return m_dir;
}

glm::vec3 Boid::getSpeed() const
{
    return m_speed;
}

float Boid::getX() const
{
    return m_pos.x;
}

float Boid::getY() const
{
    return m_pos.y;
}

void Boid::setPosition(const glm::vec2& newPos)
{
    m_pos.x = newPos.x;
    m_pos.y = newPos.y;
}

void Boid::setDirectionX(const float& dirX)
{
    m_dir.x = dirX;
}

void Boid::setDirectionY(const float& dirY)
{
    m_dir.y = dirY;
}

void Boid::move()
{
    m_pos += m_dir * m_speed;
}

void Boid::inSquare(const glm::vec3& squareSize, const float& size, const float& strength, const float& scope)
{
    glm::vec3   boundsForce = {0., 0., 0.};
    const float maxX        = squareSize.x;
    const float maxY        = squareSize.y;
    const float maxZ        = squareSize.z;
    const float minX        = -squareSize.x;
    const float minY        = -squareSize.y;
    const float minZ        = -squareSize.z;

    if (m_pos.x > squareSize.x - size - scope)
    {
        boundsForce.x = -glm::distance(m_pos.x, maxX) * (m_pos.x / maxX);
    }
    if (m_pos.x < -squareSize.x + size + scope)
    {
        boundsForce.x = glm::distance(m_pos.x, minX) * (minX / m_pos.x);
    }
    if (m_pos.y > squareSize.y - size - scope)
    {
        boundsForce.y = -glm::distance(m_pos.y, maxY) * (m_pos.y / maxY);
    }
    if (m_pos.y < -squareSize.y + size + scope)
    {
        boundsForce.y = glm::distance(m_pos.y, minY) * (minY / m_pos.y);
    }
    if (m_pos.z > squareSize.z - size - scope)
    {
        boundsForce.z = -glm::distance(m_pos.z, maxZ) * (m_pos.z / maxZ);
    }
    if (m_pos.z < -squareSize.z + size + scope)
    {
        boundsForce.z = glm::distance(m_pos.z, minZ) * (minZ / m_pos.z);
    }

    m_dir += boundsForce * strength;
    m_dir = glm::normalize(m_dir);
}

void Boid::separationForce(const std::vector<Boid>& boids, const float& scope, const float& strength)
{
    glm::vec3 totalForce = {0., 0., 0.};
    int       count      = 0;

    for (const auto& boid : boids)
    {
        if (this == &boid)
            continue;

        float distance = glm::distance(m_pos, boid.m_pos);
        if (distance < scope)
        {
            totalForce += strength * (m_pos - boid.m_pos) / distance;
            count++;
        }
    }

    if (count > 0)
    {
        totalForce /= static_cast<float>(count);
        m_dir += totalForce;
        m_dir = glm::normalize(m_dir);
    }
}

void Boid::alignementForce(const std::vector<Boid>& boids, const float& scope, const float& strength)
{
    glm::vec3 averageDirection = {0., 0., 0.};
    float     count            = 0;

    for (const auto& boid : boids)
    {
        if (this == &boid)
            continue;

        const float distance = glm::distance(m_pos, boid.m_pos);

        if (distance < scope)
        {
            averageDirection += boid.m_dir;
            count++;
        }
    }

    if (count > 0)
    {
        averageDirection /= count;
        m_dir += averageDirection * strength;
        m_dir = glm::normalize(m_dir);
    }
}

void Boid::cohesionForce(const std::vector<Boid>& boids, const float& scope, const float& strength)
{
    glm::vec3 averagePosition = {0.0, 0.0, 0.0};
    float     count           = 0;

    for (const auto& boid : boids)
    {
        if (this == &boid)
            continue;

        const float distance = glm::distance(m_pos, boid.m_pos);
        if (distance < scope)
        {
            averagePosition += boid.m_pos;
            count++;
        }
    }
    if (count > 0)
    {
        averagePosition /= count;
        m_dir += (averagePosition - m_pos) * strength;
        m_dir = glm::normalize(m_dir);
    }
}