#include "light/point_light.h"

//
// Created by Martin Minarik
//

PointLight::PointLight(int id) : Light(id) {}


const glm::vec3 &PointLight::get_position() const {
    return position;
}

void PointLight::set_position(const glm::vec3 &position) {
    PointLight::position = position;
    this->notify_observers();
}

const Attenuation &PointLight::get_attenuation() const {
    return attenuation;
}

void PointLight::set_attenuation(const Attenuation &attenuation_) {
    PointLight::attenuation = attenuation_;
    this->notify_observers();
}

void PointLight::notify_observers() {
    Observable::notify_observers(LightClasses::POINT_LIGHT);
}
