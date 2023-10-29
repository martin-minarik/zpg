#include "light/point_light.h"

//
// Created by Martin Minarik
//


PointLight::PointLight() {}

const glm::vec3 &PointLight::get_color() const {
    return color;
}

void PointLight::set_color(const glm::vec3 &color) {
    PointLight::color = color;
    this->notify_observers();
}

const glm::vec3 &PointLight::get_position() const {
    return position;
}

void PointLight::set_position(const glm::vec3 &position) {
    PointLight::position = position;
    this->notify_observers();
}
