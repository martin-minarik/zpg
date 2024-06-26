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


class Rotation : public TransformationComponent {
public:
    explicit Rotation(float angle, glm::vec3 axis);

    void apply() override;

    [[nodiscard]] const float &get_angle() const;

    [[nodiscard]] const glm::vec3 &get_axis() const;

    void set_angle(const float &value);

    void set_axis(const glm::vec3 &value);


private:
    float angle = 0;
    glm::vec3 axis = {0, 0, 0};
};
