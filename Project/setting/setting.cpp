#include "setting.hpp"

Setting::Setting(std::string fileGLTF)
    : m_planet(fileGLTF), m_rot(0.f) {}

void Setting::rotate()
{
    m_rot += 0.01;
}

void Setting::drawSetting(const p6::Shader& shader)
{
    glm::mat4   base    = glm::mat4(1.f);
    const float rotUnit = p6::PI / 300;

    m_rot += rotUnit;

    // Planet 1
    base = glm::translate(base, glm::vec3(3, -0.3, 0.2));
    base = glm::rotate(base, m_rot, glm::vec3(0.0f, 1.0f, 0.f));
    base = glm::rotate(base, p6::PI / 6, glm::vec3(1.0f, 0.0f, 0.f));
    base = glm::scale(base, glm::vec3(0.1));

    m_planet.draw(shader, base);

    base = glm::mat4(1.f);

    // Planet 2
    base = glm::translate(base, glm::vec3(0, -0.2, 2));
    base = glm::rotate(base, m_rot, glm::vec3(0.0f, 1.0f, 0.f));
    base = glm::rotate(base, p6::PI / 12, glm::vec3(1.0f, 0.0f, 0.f));
    base = glm::scale(base, glm::vec3(0.025));

    m_planet.draw(shader, base);

    base = glm::mat4(1.f);

    // Planet 3
    base = glm::translate(base, glm::vec3(-1, 0.5, 3.5));
    base = glm::rotate(base, m_rot, glm::vec3(0.0f, 1.0f, 0.f));
    base = glm::scale(base, glm::vec3(0.2));

    m_planet.draw(shader, base);

    base = glm::mat4(1.f);

    // Planet 4
    base = glm::translate(base, glm::vec3(0.5, 0., -1.5));
    base = glm::rotate(base, m_rot, glm::vec3(0.0f, 1.0f, 0.f));
    base = glm::rotate(base, -p6::PI / 7, glm::vec3(0.0f, 0.0f, 1.f));
    base = glm::scale(base, glm::vec3(0.05));

    m_planet.draw(shader, base);

    base = glm::mat4(1.f);

    // Planet 5
    base = glm::translate(base, glm::vec3(1.5, 0.6, -4));
    base = glm::rotate(base, m_rot, glm::vec3(0.0f, 1.0f, 0.f));
    base = glm::rotate(base, -p6::PI / 10, glm::vec3(1.0f, 0.0f, 0.f));
    base = glm::scale(base, glm::vec3(0.15));

    m_planet.draw(shader, base);

    base = glm::mat4(1.f);

    // Planet 6
    base = glm::translate(base, glm::vec3(-3, 0.6, -1));
    base = glm::rotate(base, m_rot, glm::vec3(0.0f, 1.0f, 0.f));
    base = glm::rotate(base, -p6::PI / 10, glm::vec3(1.0f, 0.0f, 0.f));
    base = glm::scale(base, glm::vec3(0.15));

    m_planet.draw(shader, base);
}