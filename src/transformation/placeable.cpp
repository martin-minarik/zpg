#include "transformation/placeable.h"

//
// Created by Martin Minarik
//

Placeable::Placeable() : transformation_composite(std::make_shared<TransformationComposite>()) {
    this->translation_component = this->transformation_composite->add_translation(glm::vec3{0, 0, 0});
    this->rotation_component = this->transformation_composite->add_rotation(0, glm::vec3{1, 1, 1});
    this->scale_component = this->transformation_composite->add_scale(glm::vec3{1});
}

void Placeable::set_translation(glm::vec3 value, bool apply) {
    translation_component->set_vec(value);
    if (apply)
        this->transformation_composite->apply();
}

void Placeable::set_rotation(float angle, glm::vec3 axis, bool apply) {
    rotation_component->set_angle(angle);
    rotation_component->set_axis(axis);

    if (apply)
        this->transformation_composite->apply();

}

void Placeable::set_scale(glm::vec3 value, bool apply) {
    scale_component->set_vec(value);

    if (apply)
        this->transformation_composite->apply();

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
    this->transformation_composite->add(translation_component);
    this->transformation_composite->add(rotation_component);
    this->transformation_composite->add(scale_component);
}

glm::vec3 Placeable::get_position() {
    return this->translation_component->get_vec();
}
