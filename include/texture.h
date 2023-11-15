#pragma once

//
// Created by Martin Minarik
//

// Include Glew
#include "GL/glew.h"
// Include GLFW
#include "GLFW/glfw3.h"

#include "SOIL.h"

#include <string>
#include <iostream>

class Texture {
public:
    explicit Texture() = default;

    explicit Texture(const std::string &filepath);

    virtual ~Texture();

    virtual void bind() const;

    virtual void unbind();

protected:
    GLuint texture_id;
};
