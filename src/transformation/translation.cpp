#include "transformation/translation.h"

Translation::Translation(glm::vec3 vec) : vec(vec) {

}

const glm::vec3 &Translation::get_vec() const {
    return vec;
}

void Translation::set_vec(const glm::vec3 &vec) {
    Translation::vec = vec;
}

void Translation::apply() {
    this->matrix = glm::translate(glm::mat4(1.0f), this->vec);
}


