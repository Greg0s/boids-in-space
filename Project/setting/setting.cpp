#include "setting.hpp"
#include "settingParams.hpp"

Setting::Setting(const std::string& fileGLTF)
    : m_planet(fileGLTF), m_rot(0.f) {}

void Setting::rotate()
{
    const float rotUnit = p6::PI / 800;
    m_rot += rotUnit;
}

void Setting::draw(const p6::Shader& shader, const settingParams& params)
{
    glm::mat4 base = glm::mat4(1.f);

    base = glm::translate(base, {params.pos.x, params.pos.y, params.pos.z});
    base = glm::rotate(base, m_rot, glm::vec3(0.0f, 1.0f, 0.f));
    base = glm::rotate(base, params.incl, params.inclAxis);
    base = glm::scale(base, params.scale);

    m_planet.draw(shader, base);
}

void Setting::drawSetting(const p6::Shader& shader)
{
    rotate();

    // Planet 1
    settingParams params1 = {
        glm::vec3(3, -0.3, 0.2),
        p6::PI / 6,
        glm::vec3(1.0f, 0.0f, 0.f),
        glm::vec3(0.1)};

    draw(shader, params1);

    // Planet 2
    settingParams params2 = {
        glm::vec3(0, -0.2, 2),
        p6::PI / 12,
        glm::vec3(0.0f, 1.0f, 0.f),
        glm::vec3(0.025)};

    draw(shader, params2);

    // Planet 3
    settingParams params3 = {
        glm::vec3(-1, 0.5, 3.5),
        0,
        glm::vec3(0.0f, 1.0f, 0.f),
        glm::vec3(0.2)};

    draw(shader, params3);

    // Planet 4
    settingParams params4 = {
        glm::vec3(0.5, 0., -1.5),
        -p6::PI / 7,
        glm::vec3(0.0f, 0.0f, 1.f),
        glm::vec3(0.05)};

    draw(shader, params4);

    // Planet 5
    settingParams params5 = {
        glm::vec3(1.5, 0.6, -4),
        -p6::PI / 10,
        glm::vec3(1.0f, 0.0f, 0.f),
        glm::vec3(0.15)};

    draw(shader, params5);

    // Planet 6
    settingParams params6 = {
        glm::vec3(-3, 0.6, -1),
        -p6::PI / 10,
        glm::vec3(1.0f, 0.0f, 0.f),
        glm::vec3(0.15)};

    draw(shader, params6);
}