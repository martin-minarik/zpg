#pragma once

// Include GLM
#include "glm/vec3.hpp" // glm::vec3
#include "glm/vec4.hpp" // glm::vec4
#include "glm/mat4x4.hpp" // glm::mat4
#include "glm/gtc/matrix_transform.hpp" // glm::translate, glm::rotate, glm::scale, glm::perspective
#include "glm/gtc/type_ptr.hpp" // glm::value_ptr

// std
#include <vector>
#include <memory>

#include "transformation/transformation_component.h"

class TransformationComposite : public TransformationComponent {
public:
    void apply() override;

    void add(std::shared_ptr<TransformationComponent> component);

    void remove(int index);

    void remove(std::shared_ptr<TransformationComponent> component);

    void clear();

private:
    std::vector<std::shared_ptr<TransformationComponent>> components;
};
