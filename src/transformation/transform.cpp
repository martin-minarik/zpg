#include "transformation/transform.h"


Transformation::Transformation() : matrix(glm::mat4(1.0f)) {
}

void Transformation::add(TransformationComponent *component) {
    composite.add(component);
}

void Transformation::apply() {
    composite.apply(this->matrix);
    composite.clear();
}

void TransformationComponent::clear() {

}


void TransformationComposite::add(TransformationComponent *component) {
    components.push_back(component);
}


void TransformationComposite::apply(glm::mat4 &matrix) {
    for (auto &component: components) {
        component->apply(matrix);
    }
}

void TransformationComposite::clear() {
    for (auto component: components) {
        delete component;
    }
    components.clear();
}


Translate::Translate(glm::vec3 vec) : vec(vec) {

}

void Translate::apply(glm::mat4 &matrix) {
    matrix = glm::translate(matrix, vec);
}

Rotate::Rotate(float angle, glm::vec3 axis) : angle(angle), axis(axis) {

}

void Rotate::apply(glm::mat4 &matrix) {
    matrix = glm::rotate(matrix, angle, axis);
}

Scale::Scale(glm::vec3 vec) : vec(vec) {

}

void Scale::apply(glm::mat4 &matrix) {
    matrix = glm::scale(matrix, vec);
}
