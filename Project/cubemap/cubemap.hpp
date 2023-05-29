#pragma once

#include "../include/wrapper.hpp"

inline void initCubemap(Wrapper& cubemap)
{
    // int indice = 0;

    // float cube_height2 = 10.0;
    // float z            = 0.05;

    // // top
    // cube.vertices.push_back(Vertex3D{{-10.0, 10.0, z + cube_height2}, {0.1, 0, 0}});
    // cube.vertices.push_back(Vertex3D{{10.0, 10.0, z + cube_height2}, {0.1, 0, 0}});
    // cube.vertices.push_back(Vertex3D{{10.0, -10.0, z + cube_height2}, {0.1, 0, 0}});
    // cube.vertices.push_back(Vertex3D{{-10.0, -10.0, z + cube_height2}, {0.1, 0, 0}});

    // // bottom
    // cube.vertices.push_back(Vertex3D{{-10.0, 10.0, z - cube_height2}, {0.2, 0, 0}});
    // cube.vertices.push_back(Vertex3D{{10.0, 10.0, z - cube_height2}, {0.2, 0, 0}});
    // cube.vertices.push_back(Vertex3D{{10.0, -10.0, z - cube_height2}, {0.2, 0, 0}});
    // cube.vertices.push_back(Vertex3D{{-10.0, -10.0, z - cube_height2}, {0.2, 0, 0}});

    // // top
    // cube.indices.push_back(indice + 5);
    // cube.indices.push_back(indice + 1);
    // cube.indices.push_back(indice + 4);
    // cube.indices.push_back(indice + 4);
    // cube.indices.push_back(indice + 1);
    // cube.indices.push_back(indice);

    // // Bottom
    // cube.indices.push_back(indice + 2);
    // cube.indices.push_back(indice + 6);
    // cube.indices.push_back(indice + 3);
    // cube.indices.push_back(indice + 3);
    // cube.indices.push_back(indice + 6);
    // cube.indices.push_back(indice + 7);

    // // front
    // cube.indices.push_back(indice + 2);
    // cube.indices.push_back(indice + 3);
    // cube.indices.push_back(indice);
    // cube.indices.push_back(indice);
    // cube.indices.push_back(indice + 1);
    // cube.indices.push_back(indice + 2);

    // // back
    // cube.indices.push_back(indice + 7);
    // cube.indices.push_back(indice + 6);
    // cube.indices.push_back(indice + 5);
    // cube.indices.push_back(indice + 5);
    // cube.indices.push_back(indice + 4);
    // cube.indices.push_back(indice + 7);

    // // right
    // cube.indices.push_back(indice + 1);
    // cube.indices.push_back(indice + 5);
    // cube.indices.push_back(indice + 6);
    // cube.indices.push_back(indice + 6);
    // cube.indices.push_back(indice + 2);
    // cube.indices.push_back(indice + 1);

    // // left
    // cube.indices.push_back(indice + 0);
    // cube.indices.push_back(indice + 3);
    // cube.indices.push_back(indice + 7);
    // cube.indices.push_back(indice + 7);
    // cube.indices.push_back(indice + 4);
    // cube.indices.push_back(indice + 0);

    // cube.init();

    // cube.updateVertices();
    // cubemap.init();

    float cubeSize = 5;

    // add vertices
    struct Vertex3D c1 = {glm::vec3(cubeSize, cubeSize, -cubeSize), glm::vec3(0.1, 0, 0)};
    struct Vertex3D c2 = {glm::vec3(-cubeSize, cubeSize, -cubeSize), glm::vec3(0.1, 0, 0.)};
    struct Vertex3D c3 = {glm::vec3(-cubeSize, -cubeSize, -cubeSize), glm::vec3(0.1, 0, 0)};
    struct Vertex3D c4 = {glm::vec3(cubeSize, -cubeSize, -cubeSize), glm::vec3(0.1, 0, 0)};
    struct Vertex3D c5 = {glm::vec3(cubeSize, cubeSize, cubeSize), glm::vec3(0.2, 0, 0)};
    struct Vertex3D c6 = {glm::vec3(-cubeSize, cubeSize, cubeSize), glm::vec3(0.2, 0, 0)};
    struct Vertex3D c7 = {glm::vec3(-cubeSize, -cubeSize, cubeSize), glm::vec3(0.2, 0, 0)};
    struct Vertex3D c8 = {glm::vec3(cubeSize, -cubeSize, cubeSize), glm::vec3(0.2, 0, 0)};

    cubemap.vertices.push_back(c1);
    cubemap.vertices.push_back(c2);
    cubemap.vertices.push_back(c3);
    cubemap.vertices.push_back(c4);
    cubemap.vertices.push_back(c5);
    cubemap.vertices.push_back(c6);
    cubemap.vertices.push_back(c7);
    cubemap.vertices.push_back(c8);

    // top
    cubemap.indices.push_back(0);
    cubemap.indices.push_back(1);
    cubemap.indices.push_back(2);
    cubemap.indices.push_back(0);
    cubemap.indices.push_back(2);
    cubemap.indices.push_back(3);
    // bottom
    cubemap.indices.push_back(4);
    cubemap.indices.push_back(5);
    cubemap.indices.push_back(6);
    cubemap.indices.push_back(4);
    cubemap.indices.push_back(6);
    cubemap.indices.push_back(7);
    // front
    cubemap.indices.push_back(3);
    cubemap.indices.push_back(7);
    cubemap.indices.push_back(6);
    cubemap.indices.push_back(3);
    cubemap.indices.push_back(6);
    cubemap.indices.push_back(2);
    // back
    cubemap.indices.push_back(0);
    cubemap.indices.push_back(4);
    cubemap.indices.push_back(5);
    cubemap.indices.push_back(0);
    cubemap.indices.push_back(5);
    cubemap.indices.push_back(1);
    // left
    cubemap.indices.push_back(2);
    cubemap.indices.push_back(6);
    cubemap.indices.push_back(5);
    cubemap.indices.push_back(2);
    cubemap.indices.push_back(5);
    cubemap.indices.push_back(1);
    // right
    cubemap.indices.push_back(3);
    cubemap.indices.push_back(0);
    cubemap.indices.push_back(4);
    cubemap.indices.push_back(3);
    cubemap.indices.push_back(4);
    cubemap.indices.push_back(7);

    cubemap.updateVertices();
}

inline void loadAndBindCubemap(const p6::Shader& shader, const std::vector<std::filesystem::path>& faces, const char* uniform_name, GLuint& texture_unit)
{
    GLuint texture_id = 0;
    glGenTextures(1, &texture_id);
    glBindTexture(GL_TEXTURE_CUBE_MAP, texture_id);

    int i = 0;
    for (const std::filesystem::path& texture_path : faces)
    {
        const img::Image image = p6::load_image_buffer(texture_path);
        glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0, GL_RGBA, image.width(), image.height(), 0, GL_RGBA, GL_UNSIGNED_BYTE, image.data());
        ++i;
    }

    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);

    glBindTexture(GL_TEXTURE_CUBE_MAP, 0);

    glDeleteTextures(GL_TEXTURE_CUBE_MAP, 0);

    texture_unit++;
    glActiveTexture(GL_TEXTURE0 + texture_unit);
    glUniform1i(glGetUniformLocation(shader.id(), uniform_name), texture_unit);
    glBindTexture(GL_TEXTURE_CUBE_MAP, texture_id);
}