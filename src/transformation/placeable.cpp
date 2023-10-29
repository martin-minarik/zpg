#include "transformation/placeable.h"

//
// Created by Martin Minarik
//

Placeable::Placeable() : transformation_composite(std::make_shared<TransformationComposite>()) {
}


void Placeable::add_transform(const std::shared_ptr<TransformationComponent> &component, bool apply) {
    this->transformation_composite->add(component);

    if (apply)
        this->transformation_composite->apply();
}

void Placeable::apply_transform() {
    this->transformation_composite->apply();
}

void Placeable::remove(int index) {
    this->transformation_composite->remove(index + 3);

}

void Placeable::remove(const std::shared_ptr<TransformationComponent> &component) {
    this->transformation_composite->remove(component);
}

void Placeable::clear() {
    this->transformation_composite->clear();
}

std::shared_ptr<TransformationComposite> Placeable::get_transformation_composite() {
    return this->transformation_composite;
}

std::shared_ptr<Translation> Placeable::add_translation(glm::vec3 vec, bool apply) {
    auto item = this->transformation_composite->add_translation(vec);
    if (apply)
        this->transformation_composite->apply();

    return item;
}

std::shared_ptr<Rotation> Placeable::add_rotation(float angle, glm::vec3 axis, bool apply) {
    auto item = this->transformation_composite->add_rotation(angle, axis);
    if (apply)
        this->transformation_composite->apply();

    return item;
}

std::shared_ptr<Scale> Placeable::add_scale(glm::vec3 vec, bool apply) {
    auto item = this->transformation_composite->add_scale(vec);
    if (apply)
        this->transformation_composite->apply();

    return item;
}
