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
#include <iostream>
#include <stdexcept>

#include "transformation/transformation_component.h"
#include "transformation/translation.h"
#include "transformation/rotation.h"
#include "transformation/scale.h"


class TransformationComposite : public TransformationComponent {
public:
    void apply() override;

    void add(const std::shared_ptr<TransformationComponent> &component);

    std::shared_ptr<Translation> add_translation(glm::vec3 vec);

    std::shared_ptr<Rotation> add_rotation(float angle, glm::vec3 axis);

    std::shared_ptr<Scale> add_scale(glm::vec3 vec);

    void remove(int index);

    void remove(const std::shared_ptr<TransformationComponent> &component);

    void clear();



private:
    std::vector<std::shared_ptr<TransformationComponent>> components;
};
