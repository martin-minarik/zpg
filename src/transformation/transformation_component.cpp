#include "transformation/transformation_component.h"

const glm::mat4 &TransformationComponent::get_matrix() const {
    return matrix;
}
