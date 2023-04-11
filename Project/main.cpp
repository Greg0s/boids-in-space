#include "./include/wrapper.hpp"
#include "glimac/default_shader.hpp"
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

    // Declare your infinite update loop.
    ctx.update = [&]() {
        shader.use();

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