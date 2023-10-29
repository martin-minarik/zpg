//
// Created by Martin Minarik
//

#include "shader.h"


Shader::Shader(char *vertex_shader_filepath, char *fragment_shader_filepath) {
    this->shader_program = this->loadShader(vertex_shader_filepath, fragment_shader_filepath);
}

Shader::~Shader() {
    this->deleteShader();
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

void Shader::upload(const char *name, const glm::mat4 &matrix) const {
    GLint variable = get_uniform_location(name);
    glUniformMatrix4fv(variable, 1, GL_FALSE, &matrix[0][0]);
}

void Shader::upload(const char *name, const glm::vec3 &vec) const {
    GLint variable = get_uniform_location(name);
    glUniform3fv(variable, 1, &vec[0]);
}

void Shader::upload(const char *name, const glm::vec4 &vec) const {
    GLint variable = get_uniform_location(name);
    glUniform4fv(variable, 1, &vec[0]);
}

void Shader::upload(const char *name, const float &value) const {
    GLint variable = get_uniform_location(name);
    glUniform1f(variable, value);
}

void Shader::upload(const char *name, const int &value) const {
    GLint variable = get_uniform_location(name);
    glUniform1i(variable, value);
}

void Shader::upload_transformation(TransformationComponent *transformationComponent) const {
    this->use();
    this->upload("model_matrix", transformationComponent->get_matrix());
}

void Shader::upload_material(Material *material) const {
    this->use();
    this->upload("object_color", material->get_color());
}

void Shader::update(Camera *camera) {
    this->use();
    this->upload("projection_matrix", camera->projection_matrix);
    this->upload("view_matrix", camera->view_matrix);
    this->upload("camera_position", camera->getEye());
}

void Shader::update(PointLight *light) {
    this->use();
    this->upload("light_position", light->get_position());
    this->upload("light_color", light->getColor());
}




