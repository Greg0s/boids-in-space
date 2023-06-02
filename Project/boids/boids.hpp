#pragma once

#include <cstddef>
#include <vector>
#include "../boid/boid.hpp"
#include "../loaderGLTF/Model.h"
#include "../loaderGLTF/gltf.hpp"
#include "glm/fwd.hpp"
#include "p6/p6.h"
#include "strengths-scopes.hpp"

class Boids {
private:
    std::vector<Boid> m_boids;
    size_t            m_nbBoids = 50;   // Number of boids
    const float       m_size    = 0.04; // Size of each boid

    glm::vec3 m_squareSize = {0.5f, 0.5f, 0.5f}; // Size of container
    Gltf      m_gltf;

    glm::vec3 randomPos();

public:
    Boids(const std::string& fileGLTF);

    std::vector<Boid> getBoids();

    void init();
    void draw(const p6::Shader& shaderGLTF);
    void update(scopes& scopes, strengths& strengths);
};