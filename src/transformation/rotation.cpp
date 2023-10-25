#include "transformation/rotation.h"

//
// Created by Martin Minarik
//

Rotation::Rotation(float angle, glm::vec3 axis) : TransformationComponent(), angle(angle), axis(axis) {

}

const float &Rotation::get_angle() const {
    return angle;
}

const glm::vec3 &Rotation::get_axis() const {
    return axis;
}

void Rotation::set_angle(const float &value) {
    this->angle = value;
}

void Rotation::set_axis(const glm::vec3 &value) {
    this->axis = value;
}

void Rotation::apply() {
    matrix = glm::rotate(glm::mat4(1.0f), glm::radians(angle), axis);
}




