#include "gltf.hpp"
#include "Model.h"

Gltf::Gltf(const std::string& file)
    : m_model(file.c_str()), m_base(glm::mat4(1.f)) {}

void Gltf::draw(const p6::Shader& shader)
{
    shader.use();
    shader.set("model", m_base);
    m_model.Draw(shader.id());
}

void Gltf::setBase(glm::mat4 base)
{
    m_base = base;
}
