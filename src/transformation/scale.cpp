#include "transformation/scale.h"

//
// Created by Martin Minarik
//

Scale::Scale(glm::vec3 vec) : TransformationComponent(), vec(vec) {

}

void Scale::apply() {
    this->matrix = glm::scale(glm::mat4(1.0f), vec);
}

const glm::vec3 &Scale::get_vec() {
    return this->vec;
}

void Scale::set_vec(const glm::vec3 &value) {
    this->vec = value;
}

