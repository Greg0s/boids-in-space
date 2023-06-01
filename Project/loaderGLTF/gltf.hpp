#pragma once
#include "Model.h"
#include "glm/fwd.hpp"
#include "p6/p6.h"

class Gltf {
private:
    glm::mat4 m_base;
    Model     m_model;

public:
    Gltf(const std::string& file);

    void draw(const p6::Shader& shader);

    inline Model getModel() { return m_model; };

    inline glm::mat4 getBase() { return m_base; };

    void setBase(glm::mat4 base);
};