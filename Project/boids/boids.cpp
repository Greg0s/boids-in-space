#include "boids.hpp"
#include "glm/ext/matrix_transform.hpp"
#include "glm/fwd.hpp"

glm::vec3 randomPos(glm::vec2 squareSize, float size)
{
    glm::vec2 pos2D;
    pos2D = p6::random::point(
        {
            -squareSize.x + size,
            -squareSize.y + size,
        },
        {
            squareSize.x - size,
            squareSize.y - size,
        }
    );
    return glm::vec3{pos2D.x, 0., pos2D.y};
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

    // création du vector des boids
    for (size_t i = 0; i < m_nbSquare; i++)
    {
        // square appears only in the square = center of the square
        pos = randomPos(m_squareSize, size);

        // squares have a random direction
        direction = {p6::random::direction(), 1.};

        // create the boid of the square i
        Boid boid = Boid(pos, direction, speed);

        // boid.printBoid();

        // add this boid to the others
        m_boids.push_back(boid);

        // print pos for debug
        // std::cout << "pos : " << pos.x << " " << pos.y << std::endl;
    }
}

void Boids::draw(const p6::Shader& shaderGLTF)
{
    std::string fileGLTF = "./assets/models/drone.gltf";
    Model       boidModel(fileGLTF.c_str());

    glm::mat4 base;

    for (auto& boid : m_boids)
    {
        base = glm::mat4(1.f);
        base = glm::translate(base, glm::vec3(boid.getPosition().x, boid.getPosition().y, boid.getPosition().z));
        base = glm::scale(base, glm::vec3(0.008));
        shaderGLTF.set("model", base);
        boidModel.Draw(shaderGLTF.id());
    }
}

void Boids::update(scopes scopes, strengths strengths)
{
    for (auto& boid : m_boids)
    {
        // glm::vec2 centerPoint = boids.at(i).getPosition();

        // ctx.square(p6::Center(centerPoint), p6::Radius{size});

        boid.separationForce(m_boids, scopes.scope, strengths.separationStrength);
        boid.alignementForce(m_boids, scopes.scope, strengths.alignementStrength);
        boid.cohesionForce(m_boids, scopes.scope, strengths.cohesionStrength);

        boid.move();
        // boids.at(i).inSquare(squareSize, size, strengths.boundsStrength, scopes.wallScope);
    }
}