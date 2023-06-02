#include <cstddef>
#include <fstream>
#include "./boid/boid.hpp"
#include "./camera/camera.hpp"
#include "./loaderGLTF/Model.h"
#include "./loaderGLTF/gltf.hpp"
#include "./player/player.hpp"
#include "boids/boids.hpp"
#include "glimac/default_shader.hpp"
#include "glm/ext/matrix_clip_space.hpp"
#include "glm/ext/matrix_transform.hpp"
#include "glm/fwd.hpp"
#include "p6/p6.h"
#include "setting/setting.hpp"

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

    // Load shaders

    const p6::Shader shader = p6::load_shader(
        "shaders/shader.vs.glsl",
        "shaders/shader.fs.glsl"
    );

    const p6::Shader shaderGLTF = p6::load_shader(
        "shaders/gltf.vs.glsl",
        "shaders/gltf.fs.glsl"
    );

    const p6::Shader shaderCube = p6::load_shader(
        "shaders/cube.vs.glsl",
        "shaders/cube.fs.glsl"
    );

    // Load assets

    Setting planetesSetting("./assets/models/planetesDecor.gltf");

    Gltf cube("./assets/models/cube.gltf");

    Player player("./assets/models/vaisseauFinal.gltf");

    Boids boids("./assets/models/planetesBoids.gltf");
    boids.init();

    scopes    scopes;
    strengths strengths;

    Camera camera;

    glm::vec3 lightColor(1, 0.92, 0.85);
    glm::vec3 lightPosition(0, 100, 0);

    glm::mat4 projection = glm::perspective(glm::radians(45.f), static_cast<float>(1280) / static_cast<float>(720), 0.001f, 100.0f);

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

        glm::mat4 model = glm::rotate(glm::mat4(1.0f), glm::radians(-90.0f), glm::vec3(1.0f, 0.0f, 0.0f));
        glm::mat4 view  = glm::lookAt(camera.getCoords(), player.getPos(), {0, 1, 0});

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

        planetesSetting.drawSetting(shaderGLTF);

        shaderCube.use();
        shaderCube.set("view", view);
        shaderCube.set("projection", projection);
        shaderCube.set("model", model);

        cube.draw(shaderCube, glm::mat4(1.f));
    };

    ctx.start();
}