#pragma once

#include "glm/fwd.hpp"
#include "p6/p6.h"

class Boid {
private:
    glm::vec3 m_pos   = {0., 0., 0.};
    glm::vec3 m_dir   = {0., 0., 0.};
    glm::vec3 m_speed = {0.01, 0.01, 0.01};

    void setPosition(const glm::vec2& newPos);
    void setDirectionX(const float& dirX);
    void setDirectionY(const float& dirY);

public:
    explicit Boid(glm::vec3 position, glm::vec3 direction, glm::vec3 speed)
        : m_pos(position), m_dir(direction), m_speed(speed){};

    glm::vec3 getPosition() const;
    glm::vec3 getDirection() const;
    glm::vec3 getSpeed() const;
    float     getX() const;
    float     getY() const;

    void draw(const p6::Shader& shaderGLTF);

    void printBoid() const;

    void move();
    void inSquare(const glm::vec2& squareSize, const float& size, const float& strength, const float& scope);

    void separationForce(const std::vector<Boid>& boids, float scope, float strength);
    void alignementForce(const std::vector<Boid>& boids, const float& scope, const float& strength);
    void cohesionForce(const std::vector<Boid>& boids, const float& scope, const float& strength);

    void draw(const p6::Shader& shaderGLTF) const;
};