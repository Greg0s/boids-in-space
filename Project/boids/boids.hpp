#pragma once

#include <cstddef>
#include <vector>
#include "../boid/boid.hpp"
#include "glm/fwd.hpp"
#include "p6/p6.h"
#include "strengths-scopes.hpp"

class Boids {
private:
    std::vector<Boid> m_boids;

    size_t      m_nbSquare   = 3;
    glm::vec2   m_squareSize = {0.5, 0.5};
    const float size         = 0.0;

public:
    void init();

    void draw(const p6::Shader& shaderGLTF);

    void update(scopes scopes, strengths strengths);

    std::vector<Boid> getBoids();
};