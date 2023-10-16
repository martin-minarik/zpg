#include "transformation/scale.h"

Scale::Scale(glm::vec3 vec) : vec(vec) {

}

void Scale::apply() {
    this->matrix = glm::scale(glm::mat4(1.0f), vec);
}

const glm::vec3 &Scale::get_vec() const {
    return this->vec;
}

void Scale::set_vec(const glm::vec3 &vec) {
    this->vec = vec;
}

