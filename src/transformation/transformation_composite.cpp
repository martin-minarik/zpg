#include <algorithm>
#include "transformation/transformation_composite.h"

//
// Created by Martin Minarik
//

void TransformationComposite::add(const std::shared_ptr<TransformationComponent> &component) {
    this->components.push_back(component);
}

std::shared_ptr<Translation> TransformationComposite::add_translation(glm::vec3 vec) {
    auto translation = std::make_shared<Translation>(vec);
    this->add(translation);
    return translation;
}

std::shared_ptr<Rotation> TransformationComposite::add_rotation(float angle, glm::vec3 axis) {
    auto rotation = std::make_shared<Rotation>(angle, axis);
    this->add(rotation);
    return rotation;
}

std::shared_ptr<Scale> TransformationComposite::add_scale(glm::vec3 vec) {
    auto scale = std::make_shared<Scale>(vec);
    this->add(scale);
    return scale;
}

void TransformationComposite::remove(int index) {
    if(index < this->components.size())
        this->components.erase(components.begin() + index);
    else
        throw std::runtime_error("Invalid index");
}

void TransformationComposite::remove(const std::shared_ptr<TransformationComponent> &component) {
    auto it = std::find(this->components.begin(), this->components.end(), component);
    if (it != this->components.end())
        this->components.erase(it);
}

void TransformationComposite::clear() {
    this->components.clear();
}

void TransformationComposite::apply() {
    this->matrix = glm::mat4{1.0f};
    for (auto &component: this->components) {
        component->apply();
        this->matrix *= component->get_matrix();
    }
}
