#pragma once

#include "Model.h"
#include "glm/fwd.hpp"
#include "p6/p6.h"

class Gltf {
private:
    Model m_model;

public:
    Gltf(const std::string& file);

    Model getModel() { return m_model; };

    void draw(const p6::Shader& shader, glm::mat4 base);
};