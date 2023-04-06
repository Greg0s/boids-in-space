#include "../include/vertex3D.h"
#include "glimac/default_shader.hpp"
#include "p6/p6.h"

class Wrapper {
private:
    GLuint vao;
    GLuint vbo;

public:
    std::vector<Vertex3D> vertices;
    void                  init();
    Wrapper() { init(); };
    void update();
    void draw();
};

void Wrapper::init()
{
    GLuint vbo = 0;
    glGenBuffers(1, &vbo);

    glBindBuffer(GL_ARRAY_BUFFER, vbo);

    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Vertex3D), &vertices.front(), GL_STATIC_DRAW);

    glBindBuffer(GL_ARRAY_BUFFER, 0);

    GLuint vao = 0;
    glGenVertexArrays(1, &vao);

    glBindVertexArray(vao);

    const GLuint VERTEX_ATTR_POSITION = 0;
    glEnableVertexAttribArray(VERTEX_ATTR_POSITION);

    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glVertexAttribPointer(VERTEX_ATTR_POSITION, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(GLfloat), 0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);

    glBindVertexArray(0);
}

void Wrapper::draw()
{
    glDrawArrays(GL_TRIANGLES, 0, 3);
}

void Wrapper::update()
{
    glimac::bind_default_shader();

    glClear(GL_COLOR_BUFFER_BIT);

    glBindVertexArray(vao);
    draw();
    glBindVertexArray(0);
}

void Wrapper() // desctructor
{
    glDeleteBuffers(1, &vbo);
    glDeleteVertexArrays(1, &vao);
}