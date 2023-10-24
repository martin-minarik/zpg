#include <algorithm>
#include "transformation/transformation_composite.h"

void TransformationComposite::add(const std::shared_ptr<TransformationComponent>& component) {
    this->components.push_back(component);
}

void TransformationComposite::add_translation(glm::vec3 vec) {
    this->add(std::make_shared<Translation>(vec));
}

void TransformationComposite::add_rotation(float angle, glm::vec3 axis) {
    this->add(std::make_shared<Rotation>(angle, axis));
}

void TransformationComposite::add_scale(glm::vec3 vec) {
    this->add(std::make_shared<Scale>(vec));
}

void TransformationComposite::remove(int index) {
    this->components.erase(components.begin() + index);
}

void TransformationComposite::remove(const std::shared_ptr<TransformationComponent>& component) {
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
