#include "./vertex3D.hpp"
#include "glimac/default_shader.hpp"
#include "p6/p6.h"

class Wrapper {
private:
    GLuint       vao                  = 0;
    GLuint       vbo                  = 0;
    const GLuint VERTEX_ATTR_POSITION = 0;
    const GLuint VERTEX_ATTR_COLOR    = 1;

public:
    std::vector<Vertex3D> vertices;
    void                  init();
    // Wrapper() { init(); };
    // ~Wrapper()
    // {
    //     glDeleteBuffers(1, &vbo);
    //     glDeleteVertexArrays(1, &vao);
    // };
    void update();
    // void draw();
    void print();
    void clear();
};

void Wrapper::init()
{
    glGenBuffers(1, &vbo);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Vertex3D), &vertices.front(), GL_STATIC_DRAW);
    glBindBuffer(GL_ARRAY_BUFFER, 0);

    glGenVertexArrays(1, &vao);

    glBindVertexArray(vao);

    glEnableVertexAttribArray(VERTEX_ATTR_POSITION);
    glEnableVertexAttribArray(VERTEX_ATTR_COLOR);

    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glVertexAttribPointer(VERTEX_ATTR_POSITION, 3, GL_FLOAT, GL_FALSE, 2 * sizeof(GLfloat), 0);
    glVertexAttribPointer(VERTEX_ATTR_COLOR, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (const GLvoid*)(2 * sizeof(GLfloat)));

    glBindBuffer(GL_ARRAY_BUFFER, 0);

    glBindVertexArray(0);
}

// void Wrapper::draw()
// {
//     glDrawArrays(GL_TRIANGLES, 0, vertices.size());
// }

void Wrapper::update()
{
    glClearColor(1.f, 0.5f, 0.5f, 1.f); // background color

    glClear(GL_COLOR_BUFFER_BIT);

    glBindVertexArray(vao);
    glDrawArrays(GL_TRIANGLES, 0, vertices.size());
    glBindVertexArray(0);
}

void Wrapper::print()
{
    std::cout << "vao:" << vao << std::endl;
    std::cout << "vbo:" << vbo << std::endl;
    std::cout << "vertices:" << vertices.at(1).coords[0] << std::endl;
}

void Wrapper::clear()
{
    glDeleteBuffers(1, &vbo);
    glDeleteVertexArrays(1, &vao);
}