#pragma once

#include <cstddef>
#include "./vertex3D.hpp"
#include "glimac/default_shader.hpp"
#include "p6/p6.h"

class Wrapper {
private:
    GLuint vao = 0;
    GLuint vbo = 0;
    GLuint ibo;

    const GLuint VERTEX_ATTR_POSITION = 0;
    const GLuint VERTEX_ATTR_COLOR    = 1;

public:
    std::vector<Vertex3D> vertices;
    std::vector<uint32_t> indices;
    void                  init();
    // Wrapper() { init(); };
    ~Wrapper()
    {
        glDeleteBuffers(1, &vbo);
        glDeleteVertexArrays(1, &vao);
    };
    void update();
    // void draw();
    void print();
    // void clear();
};

void Wrapper::init()
{
    glGenBuffers(1, &vbo);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);

    glBufferData(GL_ARRAY_BUFFER, indices.size() * sizeof(Vertex3D), &vertices.front(), GL_STATIC_DRAW);
    glBindBuffer(GL_ARRAY_BUFFER, 0);

    glGenBuffers(1, &ibo);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);

    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(uint32_t), &indices.front(), GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

    glGenVertexArrays(1, &vao);

    glBindVertexArray(vao);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);

    glEnableVertexAttribArray(VERTEX_ATTR_POSITION);
    glEnableVertexAttribArray(VERTEX_ATTR_COLOR);

    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glVertexAttribPointer(VERTEX_ATTR_POSITION, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex3D), (const GLvoid*)(offsetof(Vertex3D, coords)));
    glVertexAttribPointer(VERTEX_ATTR_COLOR, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex3D), (const GLvoid*)(offsetof(Vertex3D, color)));

    glBindBuffer(GL_ARRAY_BUFFER, 0);

    glBindVertexArray(0);
}

// void Wrapper::draw()
// {
//     glDrawArrays(GL_TRIANGLES, 0, vertices.size());
// }

void Wrapper::update()
{
    // glClearColor(1.f, 0.5f, 0.5f, 1.f); // background color

    glClear(GL_COLOR_BUFFER_BIT);

    glBindVertexArray(vao);
    //    glDrawArrays(GL_TRIANGLES, 0, vertices.size());
    glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, 0);

    glBindVertexArray(0);
}

void Wrapper::print()
{
    std::cout << "vao:" << vao << std::endl;
    std::cout << "vbo:" << vbo << std::endl;
    std::cout << "vertices:" << vertices.at(1).coords[0] << std::endl;
}

// void Wrapper::clear()
// {
//     glDeleteBuffers(1, &vbo);
//     glDeleteVertexArrays(1, &vao);
// }