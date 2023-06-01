#pragma once

#include "../loaderGLTF/gltf.hpp"
#include "p6/p6.h"

inline void drawSetting(Gltf planet, const p6::Shader& shader)
{
    glm::mat4 base = glm::mat4(1.f);

    base = glm::translate(base, glm::vec3(1, 0, 0.2));
    base = glm::scale(base, glm::vec3(0.1));

    planet.draw(shader, base);

    base = glm::mat4(1.f);

    base = glm::translate(base, glm::vec3(0, -0.2, 1));
    base = glm::scale(base, glm::vec3(0.1));

    planet.draw(shader, base);
}