#pragma once

#include <iostream>

#include "transformation/transformation_component.h"

//Include GLEW
#include <GL/glew.h>

#include "observer.h"
#include "camera.h"

class Shader : public Observer<Camera>
{
public:
    Shader(char *vertex_shader_str, char *fragment_shader_str);

    void use() const;

    GLint get_uniform_location(const char *name) const;

    void upload_matrix(const char *name, const glm::mat4 &matrix) const;

    void upload_transformation(TransformationComponent *transformationComponent) const;

    void update(Camera *observable) override;

private:
    void check_link_status() const;

    GLuint vertex_shader;
    GLuint fragment_shader;
    GLuint shader_program;
};