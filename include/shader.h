#pragma once

#include <iostream>

#include "transformation/transform.h"

//Include GLEW
#include <GL/glew.h>

class Shader {
public:
    Shader(char *vertex_shader_str, char *fragment_shader_str);

    void use() const;

    GLint get_uniform_location(const char *name) const;
    void upload_matrix(const char *name, glm::mat4 &matrix) const;

private:
    void check_link_status() const;

    GLuint vertex_shader;
    GLuint fragment_shader;
    GLuint shader_program;
};