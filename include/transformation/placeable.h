#pragma once

#include "transformation/transformation_composite.h"
#include "transformation/scale.h"
#include "transformation/translation.h"
#include "transformation/rotation.h"
#include <memory>

class Placeable {
public:
    Placeable();

    void set_translation(glm::vec3 value, bool apply = true);

    void set_rotation(float angle, glm::vec3 axis, bool apply = true);

    void set_scale(glm::vec3 value, bool apply = true);

    void add_transform(const std::shared_ptr<TransformationComponent> &component, bool apply = true);

    void apply_transform();

    void remove(int index);

    void remove(const std::shared_ptr<TransformationComponent> &component);

    void clear();


protected:
    std::shared_ptr<TransformationComposite> transformation_composite;
    std::shared_ptr<Translation> translation_component;
    std::shared_ptr<Rotation> rotation_component;
    std::shared_ptr<Scale> scale_component;
};

