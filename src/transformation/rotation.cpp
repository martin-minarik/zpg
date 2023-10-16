#include "transformation/rotation.h"

Rotation::Rotation(float angle, glm::vec3 axis) : angle(angle), axis(axis) {

}

const float &Rotation::get_angle() const {
    return angle;
}

void Rotation::set_angle(const float &angle) {
    this->angle = angle;
}

void Rotation::apply() {
    matrix = glm::rotate(glm::mat4(1.0f), glm::radians(angle), axis);
}


