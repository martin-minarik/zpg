#include "material/material.h"

Material::Material() {}

Material::Material(const glm::vec4 &color) : color(color) {}


float Material::get_ra() const {
    return r_a;
}

void Material::set_ra(float rA) {
    r_a = rA;
}

float Material::get_rd() const {
    return r_d;
}

void Material::set_rd(float rD) {
    r_d = rD;
}

float Material::get_rs() const {
    return r_s;

}
void Material::set_rs(float rS) {
    r_s = rS;
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



