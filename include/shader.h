#pragma once

//
// Created by Martin Minarik
//


#include <iostream>


//Include GLEW
#include <GL/glew.h>

#include "observer.h"
#include "camera.h"
#include "ShaderLoader.h"
#include "transformation/transformation_component.h"
#include "light/point_light.h"


class Shader : private ShaderLoader, public Observer<Camera>, public Observer<PointLight>
{
public:
    Shader(char *vertex_shader_filepath, char *fragment_shader_filepath);

    void use() const;

    GLint get_uniform_location(const char *name) const;

    void upload_matrix(const char *name, const glm::mat4 &matrix) const;

    void upload_transformation(TransformationComponent *transformationComponent) const;
    void upload_vec3(const char *name, const glm::vec3 &vec) const;
    void upload_vec4(const char *name, const glm::vec4 &vec) const;

    void update(Camera *observable) override;

    void update(PointLight *observable) override;

private:
    void check_link_status() const;

    GLuint shader_program;
};