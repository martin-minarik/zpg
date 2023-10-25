#include "light/point_light.h"

//
// Created by Martin Minarik
//

void PointLight::set_translation(glm::vec3 value, bool apply) {
    Placeable::set_translation(value, apply);
    notify_observers();
}

const glm::vec3 &PointLight::getColor() const {
    return color;
}

void PointLight::setColor(const glm::vec3 &color) {
    PointLight::color = color;
    notify_observers();
}
