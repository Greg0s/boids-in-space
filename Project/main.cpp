#include <cstddef>
#include <fstream>
#include "./boid/boid.hpp"
#include "./camera/camera.hpp"
#include "./include/wrapper.hpp"
#include "./loaderGLTF/Model.h"
#include "./loaderGLTF/gltf.hpp"
#include "./player/player.hpp"
#include "boids/boids.hpp"
#include "glimac/default_shader.hpp"
#include "glm/ext/matrix_clip_space.hpp"
#include "glm/ext/matrix_transform.hpp"
#include "glm/fwd.hpp"
#include "include/setting.hpp"
#include "p6/p6.h"

void moveListener(const p6::Context& ctx, Player& player, Camera& camera)
{
    if (ctx.key_is_pressed(GLFW_KEY_W))
    {
        player.goForward(ctx);
    }
    else
    {
        player.brake(ctx);
    }
    if (ctx.key_is_pressed(GLFW_KEY_S))
    {
        player.goBackward(ctx);
    }
    if (ctx.key_is_pressed(GLFW_KEY_A))
    {
        player.rotateLeft(ctx);
    }
    if (ctx.key_is_pressed(GLFW_KEY_D))
    {
        player.rotateRight(ctx);
    }
    if (ctx.key_is_pressed(GLFW_KEY_LEFT_SHIFT))
    {
        player.goUp(ctx);
    }
    if (ctx.key_is_pressed(GLFW_KEY_LEFT_CONTROL))
    {
        player.goDown(ctx);
    }
    if (ctx.key_is_pressed(GLFW_KEY_UP))
    {
        camera.closer();
    }
    if (ctx.key_is_pressed(GLFW_KEY_DOWN))
    {
        camera.further();
    }
}

int main()
{
    auto ctx = p6::Context{{1280, 720, "Boids in space"}};
    ctx.maximize_window();

    glEnable(GL_DEPTH_TEST);

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

    Gltf planeteSetting("./assets/models/planetesDecor.gltf");

    Gltf cube("./assets/models/cubeDecor.gltf");

    /*********************/

    glm::mat4 projection = glm::perspective(glm::radians(45.f), static_cast<float>(1280) / static_cast<float>(720), 0.001f, 100.0f);

    Camera camera;

    std::string playerFileGLTF = "./assets/models/vaisseauFinal.gltf";
    Player      player(playerFileGLTF);

    glm::vec3 lightColor(1, 0.92, 0.85);
    glm::vec3 lightPosition(0, 100, 0);

    scopes    scopes;
    strengths strengths;

    std::string boidsFileGLTF = "./assets/models/planetesAllegee.gltf";
    Boids       boids(boidsFileGLTF);
    boids.init();

    // Declare your infinite update loop.
    ctx.update = [&]() {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        ctx.imgui = [&]() {
            ImGui::Begin("Boids");
            ImGui::SliderFloat("Scope", &scopes.scope, 0.f, 1.f);
            ImGui::SliderFloat("Separation strength", &strengths.separationStrength, 0.f, 0.1);
            ImGui::SliderFloat("Alignement strength", &strengths.alignementStrength, 0.f, 0.1);
            ImGui::SliderFloat("Cohesion strength", &strengths.cohesionStrength, 0.f, 0.1);

            ImGui::End();
        };

        moveListener(ctx, player, camera);
        player.calcDir();
        camera.calCoords(player);

        /*********************************
         * HERE SHOULD COME THE RENDERING CODE
         *********************************/

        shader.use();
        shader.set("projection", projection);

        glm::mat4 model = glm::rotate(glm::mat4(1.0f), glm::radians(-90.0f), glm::vec3(1.0f, 0.0f, 0.0f));
        glm::mat4 view  = glm::lookAt(camera.getCoords(), player.getPos(), {0, 1, 0});

        shader.set("model", model);
        shader.set("view", view);

        // ground.update();
        // box.update();

        shaderGLTF.use();
        shaderGLTF.set("view", view);
        shaderGLTF.set("projection", projection);
        shaderGLTF.set("model", model);
        shaderGLTF.set("lightColor", lightColor);
        shaderGLTF.set("lightPosition", lightPosition);
        shaderGLTF.set("camPos", camera.getCoords());

        player.draw(shaderGLTF);

        boids.draw(shaderGLTF);
        boids.update(scopes, strengths);

        glm::mat4 base = glm::mat4(1.f);

        cube.draw(shaderGLTF, base);

        drawSetting(planeteSetting, shaderGLTF);
        // planeteDecor.draw(shaderGLTF, base);

        // cube.Draw(shaderGLTF.id());

        /*********************************/
    };

    // Should be done last. It starts the infinite loop.
    ctx.start();
    // triangle.clear();
}