#pragma once

#include <utility>
#include "../include/wrapper.hpp"

class CubemapTexture {
public:
    explicit CubemapTexture(std::vector<std::filesystem::path> faces, GLuint textureId = 0)
        : m_faces(std::move(faces)), m_textureId(textureId){};

    void load();

    void bind(const p6::Shader& shader, const char* uniformName, GLint textureUnit);

    void loadBind(const p6::Shader& shader, const char* uniformName, GLint textureUnit);

private:
    std::vector<std::filesystem::path> m_faces;
    GLuint                             m_textureId;
};

// inline void CubemapTexture::load()
// {
//     glGenTextures(1, &m_textureId);
//     glBindTexture(GL_TEXTURE_CUBE_MAP, m_textureId);

//     for (unsigned int i = 0; i < m_faces.size(); i++)
//     {
//         const img::Image face = p6::load_image_buffer(m_faces[i]);
//         glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0, GL_RGB, static_cast<int>(face.width()), static_cast<int>(face.height()), 0, GL_RGBA, GL_UNSIGNED_BYTE, face.data());
//     }

//     glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
//     glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
//     glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
//     glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
//     glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
// }

// inline void CubemapTexture::bind(const p6::Shader& shader, const char* uniformName, GLenum textureUnit)
// {
//     glGenTextures(1, &m_textureId);
//     glBindTexture(GL_TEXTURE_CUBE_MAP, m_textureId);

//     textureUnit++;
//     glActiveTexture(GL_TEXTURE0 + textureUnit);

//     glUniform1i(glGetUniformLocation(shader.id(), uniformName), static_cast<int>(textureUnit));
//     glBindTexture(GL_TEXTURE_CUBE_MAP, m_textureId);
// }

inline void CubemapTexture::loadBind(const p6::Shader& shader, const char* uniformName, GLint textureUnit)
{
    GLuint texture_id = 0;
    glGenTextures(1, &texture_id);
    glBindTexture(GL_TEXTURE_CUBE_MAP, texture_id);

    for (unsigned int i = 0; i < m_faces.size(); i++)
    {
        const img::Image face = p6::load_image_buffer(m_faces[i]);
        glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0, GL_RGB, static_cast<int>(face.width()), static_cast<int>(face.height()), 0, GL_RGBA, GL_UNSIGNED_BYTE, face.data());
    }

    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);

    glBindTexture(GL_TEXTURE_CUBE_MAP, 0);

    textureUnit++;
    glActiveTexture(GL_TEXTURE0 + textureUnit);
    glUniform1i(glGetUniformLocation(shader.id(), uniformName), textureUnit);
    glBindTexture(GL_TEXTURE_CUBE_MAP, textureUnit);
}