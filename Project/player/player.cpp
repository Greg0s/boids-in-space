#include "player.hpp"

const float rotUnit      = p6::PI / 3;
const float maxSpeed     = 0.30;
const float minSpeed     = 0.15;
const float acceleration = 0.01;

Player::Player(const std::string& fileGLTF)
    : m_rot(0), m_speed(0.04), m_gltf(fileGLTF)
{
    m_pos = {0.f, 0.01, 0.f};
    m_dir = {0.f, 0.f, 0.f};
}

void Player::goForward(const p6::Context& ctx)
{
    if (m_speed + acceleration < maxSpeed)
        m_speed += acceleration;

    m_pos.x += m_speed * m_dir.x * ctx.delta_time();
    m_pos.z += m_speed * m_dir.z * ctx.delta_time();
}

void Player::goBackward(const p6::Context& ctx)
{
    m_pos.x -= minSpeed * m_dir.x * ctx.delta_time();
    m_pos.z -= minSpeed * m_dir.z * ctx.delta_time();
}

void Player::brake(const p6::Context& ctx)
{
    if (m_speed - acceleration > minSpeed)
        m_speed -= acceleration * ctx.delta_time();
}

void Player::goUp(const p6::Context& ctx)
{
    m_pos.y += m_speed * ctx.delta_time();
}

void Player::goDown(const p6::Context& ctx)
{
    m_pos.y -= m_speed * ctx.delta_time();
}

// only change sight direction
void Player::rotateRight(const p6::Context& ctx)
{
    m_rot += rotUnit * ctx.delta_time();
}

// only change sight direction
void Player::rotateLeft(const p6::Context& ctx)
{
    m_rot -= rotUnit * ctx.delta_time();
}

void Player::move()
{
    m_pos = m_dir * m_speed;
}

void Player::calcDir()
{
    m_dir.x = glm::cos(m_rot);
    m_dir.z = glm::sin(m_rot);
}

void Player::draw(const p6::Shader& shaderGLTF)
{
    glm::mat4 base = glm::mat4(1.f);

    base = glm::translate(base, glm::vec3(m_pos.x, m_pos.y, m_pos.z));

    base = glm::rotate(base, -m_rot, glm::vec3(0.0f, 1.0f, 0.0f));
    base = glm::rotate(base, p6::PI, glm::vec3(1.0f, 0.0f, 0.0f));
    base = glm::scale(base, glm::vec3(0.05));

    m_gltf.draw(shaderGLTF, base);
}