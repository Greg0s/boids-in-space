#include "./include/wrapper.hpp"
#include "glimac/default_shader.hpp"
#include "glm/ext/matrix_clip_space.hpp"
#include "glm/ext/matrix_transform.hpp"
#include "glm/fwd.hpp"
#include "p6/p6.h"

int main()
{
    auto ctx = p6::Context{{1280, 720, "TP3 EX1"}};
    ctx.maximize_window();

    const p6::Shader shader = p6::load_shader(
        "shaders/shader.vs.glsl",
        "shaders/shader.fs.glsl"
    );

    /*********************************
     * HERE SHOULD COME THE INITIALIZATION CODE
     *********************************/

    Wrapper triangle;

    struct Vertex3D v1 = {glm::vec3(0.f, 0.f, 0.f), glm::vec3(1.f, 0.5f, 0.f)};
    struct Vertex3D v2 = {glm::vec3(-0.5f, 0.f, 0.f), glm::vec3(0.f, 1.f, 0.5f)};
    struct Vertex3D v3 = {glm::vec3(-0.5f, 0.5f, 0.f), glm::vec3(0.f, 0.5f, 1.f)};
    struct Vertex3D v4 = {glm::vec3(0.0f, 0.5f, 0.f), glm::vec3(0.f, 0.5f, 1.f)};
    triangle.vertices.push_back(v1);
    triangle.vertices.push_back(v2);
    triangle.vertices.push_back(v3);
    triangle.vertices.push_back(v4);

    triangle.indices.push_back(0);
    triangle.indices.push_back(1);
    triangle.indices.push_back(2);
    triangle.indices.push_back(0);
    triangle.indices.push_back(2);
    triangle.indices.push_back(3);

    triangle.init();

    // triangle.print();

    // GLuint vbo = 0;
    // glGenBuffers(1, &vbo);

    // glBindBuffer(GL_ARRAY_BUFFER, vbo);

    // GLfloat vertices[] = {-0.5f, -0.5f, 0.5f, -0.5f, 0.0f, 0.5f};
    // glBufferData(GL_ARRAY_BUFFER, 6 * sizeof(GLfloat), vertices, GL_STATIC_DRAW);

    // glBindBuffer(GL_ARRAY_BUFFER, 0);

    // GLuint vao = 0;
    // glGenVertexArrays(1, &vao);

    // glBindVertexArray(vao);

    // const GLuint VERTEX_ATTR_POSITION = 0;
    // glEnableVertexAttribArray(VERTEX_ATTR_POSITION);

    // glBindBuffer(GL_ARRAY_BUFFER, vbo);
    // glVertexAttribPointer(VERTEX_ATTR_POSITION, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(GLfloat), 0);
    // glBindBuffer(GL_ARRAY_BUFFER, 0);

    // glBindVertexArray(0);

    /*********************/

    // matrice de projection, permet de delimiter champ qu'on voit, fait perspective
    // perspective(fov, aspect ratio fenetre,distance min, distance max)
    glm::mat4 projection = glm::perspective(glm::radians(45.f), static_cast<float>(1280) / static_cast<float>(720), 0.001f, 100.0f);

    // Declare your infinite update loop.
    ctx.update = [&]() {
        shader.use();
        // envoie matrice au shader
        shader.set("projection", projection);

        // "world", translation/rotation etc d'un objet
        // rotate(matrice courante (identité car c'est la 1ère transfo), rotation, axe autour duquel se fait rotation)
        glm::mat4 model = glm::rotate(glm::mat4(1.0f), glm::radians(-90.0f), glm::vec3(1.0f, 0.0f, 0.0f));
        // model = glm::translate(model, )
        // matrice normale, définit où va être cam
        // lookAt(pos ete, centre d'ou tu regarde, où est le haut)
        // fc fait en sorte que l'horizon est tjrs droit
        glm::mat4 view = glm::lookAt({0.25, 0.5, 0.25}, glm::vec3(0), {0, 1, 0});

        shader.set("model", model);
        shader.set("view", view);

        /*********************************
         * HERE SHOULD COME THE RENDERING CODE
         *********************************/
        // glimac::bind_default_shader();
        triangle.update();

        // glimac::bind_default_shader();

        // glClearColor(1.f, 0.5f, 0.5f, 1.f); // background color

        // glClear(GL_COLOR_BUFFER_BIT);

        // glBindVertexArray(vao);
        // glDrawArrays(GL_TRIANGLES, 0, 3);
        // glBindVertexArray(0);
        /*********************************/
    };

    // Should be done last. It starts the infinite loop.
    ctx.start();
    // triangle.clear();
}