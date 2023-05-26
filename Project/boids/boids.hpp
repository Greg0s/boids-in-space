#pragma once

#include <cstddef>
#include <vector>
#include "../boid/boid.hpp"
#include "../loaderGLTF/Model.h"
#include "glm/fwd.hpp"
#include "p6/p6.h"
#include "strengths-scopes.hpp"

class Boids {
private:
    std::vector<Boid> m_boids;

    size_t    m_nbSquare   = 20;
    glm::vec3 m_squareSize = {0.5f, 0.5f, 0.5f};
    // values = size from the center of the square = total square size /2
    const float m_size = 0.05;

public:
    void init();

    void draw(const p6::Shader& shaderGLTF);

    void update(scopes scopes, strengths strengths);

    std::vector<Boid> getBoids();
};