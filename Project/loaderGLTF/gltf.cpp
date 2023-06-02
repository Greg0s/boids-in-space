#include "gltf.hpp"

Gltf::Gltf(const std::string& file)
    : m_model(file.c_str()) {}

void Gltf::draw(const p6::Shader& shader, glm::mat4 base)
{
    shader.set("model", base);
    m_model.Draw(shader.id());
}
