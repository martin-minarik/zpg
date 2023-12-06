#pragma once

//
// Created by Martin Minarik
//

// Include GLM
#include "glm/vec3.hpp" // glm::vec3
#include "glm/vec4.hpp" // glm::vec4
#include "glm/mat4x4.hpp" // glm::mat4
#include "glm/gtc/matrix_transform.hpp" // glm::translate, glm::rotate, glm::scale, glm::perspective
#include "glm/gtc/type_ptr.hpp" // glm::value_ptr

#include "transformation/transformation_component.h"


class Bezier : public TransformationComponent {
public:
    explicit Bezier(glm::mat4x3 points, float param_t);
    void apply() override;

    float get_param_t() const;

    void set_param_t(float param_t);

private:
    glm::mat4x3 points;
    float param_t;

    glm::mat4 coefficients = glm::mat4(glm::vec4(-1.0, 3.0, -3.0, 1.0),
                                       glm::vec4(3.0, -6.0, 3.0, 0),
                                       glm::vec4(-3.0, 3.0, 0, 0),
                                       glm::vec4(1, 0, 0, 0));
};


