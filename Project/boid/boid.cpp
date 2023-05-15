#include "./boid.hpp"
#include "../loaderGLTF/Model.h"
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

void Boid::printBoid() const
{
    std::cout << "-------BOID----------" << std::endl;
    std::cout << "Pos: x " << m_pos.x << " y " << m_pos.y << std::endl;
    std::cout << "Dir: x " << m_dir.x << " y " << m_dir.y << std::endl;
    std::cout << "v: x " << m_speed.x << " y " << m_speed.y << std::endl;
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

void Boid::inSquare(const glm::vec2& squareSize, const float& size, const float& strength, const float& scope)
{
    glm::vec3   boundsForce = {0., 0., 0.};
    const float maxX        = 1;
    const float maxY        = 1;
    const float minX        = -1;
    const float minY        = -1;

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

    m_dir += boundsForce * strength;
    m_dir = glm::normalize(m_dir);
}

void Boid::separationForce(const std::vector<Boid>& boids, float scope, float strength)
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

void Boid::draw(const p6::Shader& shaderGLTF)
{
    std::string fileGLTF = "./assets/models/drone.gltf";
    Model       boid(fileGLTF.c_str());

    glm::mat4 base = glm::mat4(1.f);
    base           = glm::translate(base, glm::vec3(m_pos.x, m_pos.y, m_pos.z));

    base = glm::scale(base, glm::vec3(0.01));

    shaderGLTF.set("model", base);
    boid.Draw(shaderGLTF.id());
}

static void Boid::update(std::vector<Boid> boids, scopes scopes, strengths strengths)
{
    int nbSquare = 50;
    for (size_t i = 0; i < nbSquare; i++)
    {
        glm::vec2 centerPoint = boids.at(i).getPosition();

        ctx.square(p6::Center(centerPoint), p6::Radius{size});

        boids.at(i).separationForce(boids, scopes.scope, strengths.separationStrength);
        boids.at(i).alignementForce(boids, scopes.scope, strengths.alignementStrength);
        boids.at(i).cohesionForce(boids, scopes.scope, strengths.cohesionStrength);

        boids.at(i).move();
        boids.at(i).inSquare(squareSize, size, strengths.boundsStrength, scopes.wallScope);
    }
}