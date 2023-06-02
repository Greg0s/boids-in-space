#pragma once

#include "../loaderGLTF/gltf.hpp"
#include "p6/p6.h"
#include "settingParams.hpp"

class Setting {
private:
    Gltf m_planet;

    float m_rot;

public:
    Setting(const std::string& fileGLTF);

    void rotate();
    void draw(const p6::Shader& shader, const settingParams& params);
    void drawSetting(const p6::Shader& shader);
};