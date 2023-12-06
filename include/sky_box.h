#pragma once

//
// Created by Martin Minarik
//

#include <vector>

#include <GL/glew.h>

#include "shader.h"
#include "models/vertices/skycube.h"
#include "sky_box_texture.h"

class SkyBox{
public:
    SkyBox(Shader &shader, const shared_ptr<SkyBoxTexture> &texture);

    virtual ~SkyBox();

    [[nodiscard]] float get_intensity() const;

    void set_intensity(float intensity);

    void draw();

private:
    Shader &shader;
    GLuint VBO = 0;
    GLuint VAO = 0;
    std::shared_ptr<SkyBoxTexture> texture;
    float intensity = 1;
};

