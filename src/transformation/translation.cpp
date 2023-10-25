#include "transformation/translation.h"

//
// Created by Martin Minarik
//

Translation::Translation(glm::vec3 vec) : TransformationComponent(), vec(vec) {

}

const glm::vec3 &Translation::get_vec() const {
    return vec;
}

void Translation::set_vec(const glm::vec3 &value) {
    Translation::vec = value;
}

void Translation::apply() {
    this->matrix = glm::translate(glm::mat4(1.0f), this->vec);
}


