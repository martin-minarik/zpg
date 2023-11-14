#pragma once

// Include Glew
#include "GL/glew.h"
// Include GLFW
#include "GLFW/glfw3.h"

#include "SOIL.h"

#include <string>

class Texture
{
public:
    explicit Texture(const std::string& filepath);

    virtual ~Texture();

    void bind() const;
    static void unbind() ;
private:
    GLuint texture_id;
};
