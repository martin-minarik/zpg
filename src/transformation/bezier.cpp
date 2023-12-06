#include "transformation/bezier.h"

//
// Created by Martin Minarik
//


Bezier::Bezier(glm::mat4x3 points, float param_t) : points(points), param_t(param_t) {

}

void Bezier::apply() {
    glm::vec4 parameters = glm::vec4(pow(param_t, 3),
                                     pow(param_t, 2),
                                     param_t,
                                     1.0f);

    glm::vec3 point = parameters * this->coefficients * glm::transpose(points);

    this->matrix = glm::translate(glm::mat4(1.0f), point);
}

float Bezier::get_param_t() const {
    return param_t;
}

void Bezier::set_param_t(float param_t) {
    this->param_t = param_t;
}
