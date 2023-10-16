#include <algorithm>
#include "transformation/transformation_composite.h"

void TransformationComposite::add(std::shared_ptr<TransformationComponent> component) {
    this->components.push_back(component);
}

void TransformationComposite::remove(int index) {
    this->components.erase(components.begin() + index);
}

void TransformationComposite::remove(std::shared_ptr<TransformationComponent> component) {
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
