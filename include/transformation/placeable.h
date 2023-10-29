#pragma once

//
// Created by Martin Minarik
//

#include "transformation/transformation_composite.h"
#include "transformation/scale.h"
#include "transformation/translation.h"
#include "transformation/rotation.h"
#include <memory>


class Placeable {
public:
    Placeable();

    void add_transform(const std::shared_ptr<TransformationComponent> &component, bool apply = true);

    std::shared_ptr<Translation> add_translation(glm::vec3 vec, bool apply = true);

    std::shared_ptr<Rotation> add_rotation(float angle, glm::vec3 axis, bool apply = true);

    std::shared_ptr<Scale> add_scale(glm::vec3 vec, bool apply = true);

    void apply_transform();

    void remove(int index);

    void remove(const std::shared_ptr<TransformationComponent> &component);

    void clear();

    std::shared_ptr<TransformationComposite> get_transformation_composite();


protected:
    std::shared_ptr<TransformationComposite> transformation_composite;
};

