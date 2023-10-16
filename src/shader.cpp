#include "shader.h"
#include "Camera.h"

Shader::Shader(char *vertex_shader_str, char *fragment_shader_str) {

    //create and compile shaders
    vertex_shader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertex_shader, 1, &vertex_shader_str, nullptr);
    glCompileShader(vertex_shader);
    fragment_shader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragment_shader, 1, &fragment_shader_str, nullptr);
    glCompileShader(fragment_shader);
    shader_program = glCreateProgram();
    glAttachShader(shader_program, fragment_shader);
    glAttachShader(shader_program, vertex_shader);
    glLinkProgram(shader_program);

    check_link_status();
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

void Shader::upload_transformation(TransformationComponent *transformationComponent) const {
//    this->use();
    this->upload_matrix("model_matrix", transformationComponent->get_matrix());
}

void Shader::camera_update(Camera *camera) const {
    this->use();
    this->upload_matrix("projection_matrix", camera->projection_matrix);
    this->upload_matrix("view_matrix", camera->view_matrix);
}


