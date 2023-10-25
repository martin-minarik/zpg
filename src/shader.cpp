#include "shader.h"

//
// Created by Martin Minarik
//

Shader::Shader(char *vertex_shader_filepath, char *fragment_shader_filepath) {
    this->shader_program = this->loadShader(vertex_shader_filepath, fragment_shader_filepath);
}


void Shader::use() const {
    glUseProgram(this->shader_program);
}

void Shader::check_link_status() const {
    GLint status;
    glGetProgramiv(shader_program, GL_LINK_STATUS, &status);
    if (status == GL_FALSE) {
        GLint infoLogLength;
        glGetProgramiv(shader_program, GL_INFO_LOG_LENGTH, &infoLogLength);
        auto *strInfoLog = new GLchar[infoLogLength + 1];
        glGetProgramInfoLog(shader_program, infoLogLength, nullptr, strInfoLog);
        fprintf(stderr, "Linker failure: %s\n", strInfoLog);
        delete[] strInfoLog;
    }
}

GLint Shader::get_uniform_location(const char *name) const {
    return glGetUniformLocation(shader_program, name);
}

void Shader::upload_matrix(const char *name, const glm::mat4 &matrix) const {
    GLint variable = get_uniform_location(name);
    glUniformMatrix4fv(variable, 1, GL_FALSE, &matrix[0][0]);
}

void Shader::upload_vec3(const char *name, const glm::vec3 &vec) const {
    GLint variable = get_uniform_location(name);
    glUniform3fv(variable, 1, &vec[0]);
}

void Shader::upload_vec4(const char *name, const glm::vec4 &vec) const {
    GLint variable = get_uniform_location(name);
    glUniform4fv(variable, 1, &vec[0]);
}

void Shader::upload_transformation(TransformationComponent *transformationComponent) const {
    this->upload_matrix("model_matrix", transformationComponent->get_matrix());
}

void Shader::update(Camera *camera) {
    this->use();
    this->upload_matrix("projection_matrix", camera->projection_matrix);
    this->upload_matrix("view_matrix", camera->view_matrix);
    this->upload_vec3("camera_position", camera->getEye());
}

void Shader::update(PointLight *light) {
    this->use();
    this->upload_vec3("light_position", light->get_position());
    this->upload_vec3("light_color", light->getColor());
}




