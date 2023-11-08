#include "light/spotlight.h"

Spotlight::Spotlight(int id) : Light(id) {

}

void Spotlight::notify_observers() {
    Observable::notify_observers(LightClasses::SPOT_LIGHT);
}

const glm::vec3 &Spotlight::get_position() const {
    return position;
}

void Spotlight::set_position(const glm::vec3 &position) {
    Spotlight::position = position;
    notify_observers();
}

const glm::vec3 &Spotlight::get_direction() const {
    return direction;
}

void Spotlight::set_direction(const glm::vec3 &direction) {
    Spotlight::direction = direction;
    notify_observers();
}

const Attenuation &Spotlight::get_attenuation() const {
    return attenuation;
}

void Spotlight::set_attenuation(const Attenuation &attenuation) {
    Spotlight::attenuation = attenuation;
    notify_observers();
}

float Spotlight::get_cut_off() const {
    return cut_off;
}

void Spotlight::set_cut_off(float cutOff) {
    cut_off = cutOff;
    notify_observers();
}

void Spotlight::update(Camera *camera) {
    this->position = camera->get_eye();
    this->direction = camera->get_target();
    notify_observers();
}

