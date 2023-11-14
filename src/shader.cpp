#include "shader.h"

//
// Created by Martin Minarik
//


Shader::Shader(char *vertex_shader_filepath, char *fragment_shader_filepath) {
    this->shader_program = this->loadShader(vertex_shader_filepath, fragment_shader_filepath);
}

Shader::~Shader() {
    this->deleteShader();
}

void Shader::use() const {
    glUseProgram(this->shader_program);
}

void Shader::unbind() const {
    glUseProgram(0);
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

void Shader::upload(const char *name, const bool &value) const {
    GLint variable = get_uniform_location(name);
    glUniform1i(variable, value);
}

void Shader::upload_transformation(TransformationComponent *transformationComponent) const {
    this->use();
    this->upload("model_matrix", transformationComponent->get_matrix());
    this->unbind();
}

void Shader::upload_material(Material *material) const {
    this->use();
    this->upload("object_color", material->get_color());
    this->upload("ambient_color", material->get_ambient_color());
    this->upload("r_a", material->get_ra());
    this->upload("r_d", material->get_rd());
    this->upload("r_s", material->get_rs());
    this->upload("specular_power", material->get_specular_power());

    const auto& texture = material->get_texture();
    if(texture)
    {
        this->upload("has_texture", true);
        this->upload_texture(texture.get());
    }
    else
        this->upload("has_texture", false);
}

void Shader::upload_texture(Texture *texture) const
{
    texture->bind();
}

void Shader::update(Camera *camera) {
    this->use();
    this->upload("projection_matrix", camera->projection_matrix);
    this->upload("view_matrix", camera->view_matrix);
    this->upload("camera_position", camera->get_eye());
}

void Shader::update(Light *light, int descriptor) {
    this->use();

    std::string item_locator = "lights[" + std::to_string(light->get_id()) + "]";
    this->upload((item_locator + ".color").c_str(), light->get_color());

    if (descriptor == LightClasses::POINT_LIGHT) {
        auto &point_light = dynamic_cast<PointLight &>(*light);
        this->upload((item_locator + ".position").c_str(), point_light.get_position());

        const Attenuation &attenuation = point_light.get_attenuation();
        this->upload((item_locator + ".k_constant").c_str(), attenuation.k_constant);
        this->upload((item_locator + ".k_linear").c_str(), attenuation.k_linear);
        this->upload((item_locator + ".k_quadratic").c_str(), attenuation.k_quadratic);

        this->upload((item_locator + ".type").c_str(), 0);

    } else if (descriptor == LightClasses::DIRECTIONAL_LIGHT) {
        auto &directional_light = dynamic_cast<DirectionalLight &>(*light);
        this->upload((item_locator + ".direction").c_str(), directional_light.get_direction());
        this->upload((item_locator + ".type").c_str(), 1);

    } else if (descriptor == LightClasses::SPOT_LIGHT) {
        auto &spotlight = dynamic_cast<Spotlight &>(*light);
        this->upload((item_locator + ".position").c_str(), spotlight.get_position());
        this->upload((item_locator + ".direction").c_str(), spotlight.get_direction());

        const Attenuation &attenuation = spotlight.get_attenuation();
        this->upload((item_locator + ".k_constant").c_str(), attenuation.k_constant);
        this->upload((item_locator + ".k_linear").c_str(), attenuation.k_linear);
        this->upload((item_locator + ".k_quadratic").c_str(), attenuation.k_quadratic);

        this->upload((item_locator + ".cut_off").c_str(), spotlight.get_cut_off());

        this->upload((item_locator + ".type").c_str(), 2);
    }
}

void Shader::upload_number_of_lights(int n) const {
    this->use();
    this->upload("n_lights", n);
}



