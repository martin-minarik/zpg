#include "material/material.h"

//
// Created by Martin Minarik
//

Material::Material() {}

Material::Material(const glm::vec4 &color) : color(color) {}


float Material::get_ra() const {
    return r_a;
}

void Material::set_ra(float ra) {
    r_a = ra;
}

float Material::get_rd() const {
    return r_d;
}

void Material::set_rd(float rd) {
    r_d = rd;
}

float Material::get_rs() const {
    return r_s;

}
void Material::set_rs(float rs) {
    r_s = rs;
}

int Material::get_specular_power() const {
    return specular_power;
}

void Material::set_specular_power(int specularPower) {
    specular_power = specularPower;
}

const glm::vec4 &Material::get_color() const {
    return color;

}

void Material::set_color(const glm::vec4 &color_) {
    color = color_;
}

const glm::vec4 &Material::get_ambient_color() const {
    return ambient_color;
}

void Material::set_ambient_color(const glm::vec4 &ambientColor) {
    ambient_color = ambientColor;
}



