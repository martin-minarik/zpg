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

class TransformationComponent{
public:
    virtual ~TransformationComponent() = default;

    virtual void apply() = 0;

    [[nodiscard]] const glm::mat4 &get_matrix() const;

protected:
    glm::mat4 matrix = glm::mat4{1.f};
};
