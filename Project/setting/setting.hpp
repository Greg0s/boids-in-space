#pragma once

#include "../loaderGLTF/gltf.hpp"
#include "p6/p6.h"

class Setting {
private:
    Gltf  m_planet;
    float m_rot;

public:
    explicit Setting(std::string fileGLTF);

    void rotate();
    void drawSetting(const p6::Shader& shader);
};