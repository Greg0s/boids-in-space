#include "boids.hpp"
#include "glm/ext/matrix_transform.hpp"
#include "glm/fwd.hpp"

Boids::Boids(const std::string& fileGLTF)
    : m_gltf(fileGLTF) {}

std::vector<Boid> Boids::getBoids()
{
    return m_boids;
}

glm::vec3 Boids::randomPos()
{
    float x = p6::random::number(-m_squareSize.x + m_size, m_squareSize.x - m_size);
    float y = p6::random::number(-m_squareSize.y + m_size, m_squareSize.y - m_size);
    float z = p6::random::number(-m_squareSize.z + m_size, m_squareSize.z - m_size);

    return glm::vec3{x, y, z};
}

void Boids::init()
{
    glm::vec3 pos;
    glm::vec3 direction;
    glm::vec3 speed = {0.008, 0.008, 0.008};

    // vector<Boid> creation
    for (size_t i = 0; i < m_nbBoids; i++)
    {
        // square appears only in the square = center of the square
        pos = randomPos();
        // squares have a random direction
        direction = {p6::random::direction(), 1.};
        // create the boid of the square i
        Boid boid = Boid(pos, direction, speed);
        // add this boid to the others
        m_boids.push_back(boid);
    }
}

void Boids::draw(const p6::Shader& shaderGLTF)
{
    glm::mat4 base;

    for (auto& boid : m_boids)
    {
        base = glm::mat4(1.f);
        base = glm::translate(base, glm::vec3(boid.getPosition().x, boid.getPosition().y, boid.getPosition().z));
        base = glm::scale(base, glm::vec3(0.04));

        shaderGLTF.set("model", base);
        m_gltf.getModel().Draw(shaderGLTF.id());
    }
}

void Boids::update(scopes& scopes, strengths& strengths)
{
    for (auto& boid : m_boids)
    {
        boid.separationForce(m_boids, scopes.scope, strengths.separationStrength);
        boid.alignementForce(m_boids, scopes.scope, strengths.alignementStrength);
        boid.cohesionForce(m_boids, scopes.scope, strengths.cohesionStrength);

        boid.move();
        boid.inSquare(m_squareSize, m_size, strengths.boundsStrength, scopes.wallScope);
    }
}
