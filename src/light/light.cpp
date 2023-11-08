#include "light/light.h"

//
// Created by Martin Minarik
//

Light::Light(int id) : id(id) {}

const glm::vec3 &Light::get_color() const {
    return color;
}

void Light::set_color(const glm::vec3 &color) {
    Light::color = color;
    this->notify_observers();
}

int Light::get_id() const {
    return id;
}

void Light::notify_observers() {
    Observable::notify_observers(LightClasses::LIGHT_BASE);
}
