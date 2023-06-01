#include "boids.hpp"
#include "glm/ext/matrix_transform.hpp"
#include "glm/fwd.hpp"

Boids::Boids(std::string fileGLTF)
    : m_gltf(fileGLTF)
{}

glm::vec3 randomPos(glm::vec3 squareSize, float size)
{
    float x = p6::random::number(-squareSize.x + size, squareSize.x - size);
    float y = p6::random::number(-squareSize.y + size, squareSize.y - size);
    float z = p6::random::number(-squareSize.z + size, squareSize.z - size);

    return glm::vec3{x, y, z};
}

std::vector<Boid> Boids::getBoids()
{
    return m_boids;
}

void Boids::init()
{
    glm::vec3 pos;
    glm::vec3 direction;
    glm::vec3 speed = {0.008, 0.008, 0.008};

    // vector<Boid> creation
    for (size_t i = 0; i < m_nbSquare; i++)
    {
        // square appears only in the square = center of the square
        pos = randomPos(m_squareSize, m_size);
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
    // std::string fileGLTF = "./assets/models/planetesAllegee.gltf";
    // Model       boidModel(fileGLTF.c_str());

    glm::mat4 base;

    for (auto& boid : m_boids)
    {
        base = glm::mat4(1.f);
        base = glm::translate(base, glm::vec3(boid.getPosition().x, boid.getPosition().y, boid.getPosition().z));
        base = glm::scale(base, glm::vec3(0.008));

        shaderGLTF.set("model", base);
        m_gltf.getModel().Draw(shaderGLTF.id());
    }
}

void Boids::update(scopes scopes, strengths strengths)
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