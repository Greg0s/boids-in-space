#include <fstream>
#include "./boid/boid.hpp"
#include "./camera/camera.hpp"
#include "./include/wrapper.hpp"
#include "./loaderGLTF/Model.h"
#include "./player/player.hpp"
#include "glimac/default_shader.hpp"
#include "glm/ext/matrix_clip_space.hpp"
#include "glm/ext/matrix_transform.hpp"
#include "glm/fwd.hpp"
#include "p6/p6.h"

struct strengths {
    const float boundsStrength     = 1;
    float       separationStrength = 0.04; // 2
    float       alignementStrength = 0.03; // 5
    float       cohesionStrength   = 0.01; // 5
};

struct scopes {
    float       scope     = 0.5;
    const float wallScope = 0.1;
};

glm::vec2 randomPos(glm::vec2 squareSize, float size)
{
    glm::vec2 pos;
    return pos = p6::random::point(
               {
                   -squareSize.x + size,
                   -squareSize.y + size,
               },
               {
                   squareSize.x - size,
                   squareSize.y - size,
               }
           );
}

std::vector<Boid> boidsVec(size_t nbSquare, glm::vec2 squareSize, float size)
{
    std::vector<Boid> boids;

    glm::vec3 pos;
    glm::vec3 direction;
    // glm::vec3 speed = {0.008, 0.008, 0.008};

    // création du vector des boids
    for (size_t i = 0; i < nbSquare; i++)
    {
        // square appears only in the square = center of the square
        pos = {randomPos(squareSize, size), 1.};

        // squares have a random direction
        direction = {p6::random::direction(), 1.};

        // create the boid of the square i
        Boid boid;

        // add this boid to the others
        boids.push_back(boid);

        // print pos for debug
        // std::cout << "pos : " << pos.x << " " << pos.y << std::endl;
    }
    return boids;
}

void moveListener(const p6::Context& ctx, Player& player)
{
    if (ctx.key_is_pressed(GLFW_KEY_W))
    {
        player.goForward();
    }
    if (ctx.key_is_pressed(GLFW_KEY_S))
    {
        player.goBackward();
    }
    if (ctx.key_is_pressed(GLFW_KEY_A))
    {
        player.goLeft();
    }
    if (ctx.key_is_pressed(GLFW_KEY_D))
    {
        player.goRight();
    }
}

int main()
{
    // Const declaration
    scopes    scopes;
    strengths strengths;

    auto ctx = p6::Context{{1280, 720, "Boids in space"}};
    ctx.maximize_window();

    const p6::Shader shader = p6::load_shader(
        "shaders/shader.vs.glsl",
        "shaders/shader.fs.glsl"
    );

    const p6::Shader shaderGLTF = p6::load_shader(
        "shaders/gltf.vs.glsl",
        "shaders/gltf.fs.glsl"
    );

    /*********************************
     * HERE SHOULD COME THE INITIALIZATION CODE
     *********************************/

    Wrapper ground;

    struct Vertex3D g1 = {glm::vec3(0.f, 0.f, 0.f), glm::vec3(1.f, 0.5f, 0.f)};
    struct Vertex3D g2 = {glm::vec3(-0.5f, 0.f, 0.f), glm::vec3(0.f, 1.f, 0.5f)};
    struct Vertex3D g3 = {glm::vec3(-0.5f, 0.5f, 0.f), glm::vec3(0.f, 0.5f, 1.f)};
    struct Vertex3D g4 = {glm::vec3(0.0f, 0.5f, 0.f), glm::vec3(0.f, 0.5f, 1.f)};
    ground.vertices.push_back(g1);
    ground.vertices.push_back(g2);
    ground.vertices.push_back(g3);
    ground.vertices.push_back(g4);

    ground.indices.push_back(0);
    ground.indices.push_back(1);
    ground.indices.push_back(2);
    ground.indices.push_back(0);
    ground.indices.push_back(2);
    ground.indices.push_back(3);

    ground.init();

    // Wrapper player;

    // struct Vertex3D p1 = {glm::vec3(0.f, 0.f, 0.f), glm::vec3(1.f, 1.f, 1.f)};
    // struct Vertex3D p2 = {glm::vec3(-0.01f, 0.f, 0.f), glm::vec3(1.f, 1.f, 1.f)};
    // struct Vertex3D p3 = {glm::vec3(-0.01f, 0.01f, 0.f), glm::vec3(1.f, 1.f, 1.f)};
    // struct Vertex3D p4 = {glm::vec3(0.0f, 0.01f, 0.f), glm::vec3(1.f, 1.f, 1.f)};

    /*********************/

    // matrice de projection, permet de delimiter champ qu'on voit, fait perspective
    // perspective(fov, aspect ratio fenetre,distance min, distance max)
    glm::mat4 projection = glm::perspective(glm::radians(45.f), static_cast<float>(1280) / static_cast<float>(720), 0.001f, 100.0f);

    Camera camera;
    Player player;

    glm::vec3 lightColor(1, 0.92, 0.85);
    glm::vec3 lightPosition(0, 100, 0);

    // Declare your infinite update loop.
    ctx.update = [&]() {
        shader.use();
        // envoie matrice au shader
        shader.set("projection", projection);

        // camera.setDistance(camera.getDistance() + 0.01);
        // posTest += glm::vec3(0.1, 0.1, 0.);

        // "world", translation/rotation etc d'un objet
        // rotate(matrice courante (identité car c'est la 1ère transfo), rotation, axe autour duquel se fait rotation)
        glm::mat4 model = glm::rotate(glm::mat4(1.0f), glm::radians(-90.0f), glm::vec3(1.0f, 0.0f, 0.0f));
        // model = glm::translate(model, )
        // matrice normale, définit où va être cam
        // lookAt(pos ete, centre d'ou tu regarde, où est le haut)
        // fc fait en sorte que l'horizon est tjrs droit
        camera.calCoords(player.getPos());

        glm::mat4 view = glm::lookAt(camera.getCoords(), player.getPos(), {0, 1, 0});

        shader.set("model", model);
        shader.set("view", view);

        ground.update();

        moveListener(ctx, player);

        shaderGLTF.use();
        shaderGLTF.set("view", view);
        shaderGLTF.set("projection", projection);
        shaderGLTF.set("model", model);
        shaderGLTF.set("lightColor", lightColor);
        shaderGLTF.set("lightPosition", lightPosition);
        shaderGLTF.set("camPos", camera.getCoords());

        player.draw(shaderGLTF);

        // cube.Draw(shaderGLTF.id());

        /*********************************
         * HERE SHOULD COME THE RENDERING CODE
         *********************************/
        // glimac::bind_default_shader();

        /*********************************/
    };

    // Should be done last. It starts the infinite loop.
    ctx.start();
    // triangle.clear();
}