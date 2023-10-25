#include "transformation/transformation_component.h"

//
// Created by Martin Minarik
//

const glm::mat4 &TransformationComponent::get_matrix() const {
    return matrix;
}
