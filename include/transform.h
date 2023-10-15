#pragma once

// Include GLM
#include "glm/vec3.hpp" // glm::vec3
#include "glm/vec4.hpp" // glm::vec4
#include "glm/mat4x4.hpp" // glm::mat4
#include "glm/gtc/matrix_transform.hpp" // glm::translate, glm::rotate, glm::scale, glm::perspective
#include "glm/gtc/type_ptr.hpp" // glm::value_ptr

// std
#include <vector>

class TransformationComponent {
public:
    virtual ~TransformationComponent() = default;

    virtual void apply(glm::mat4 &matrix) = 0;

    virtual void clear();
};

class TransformationComposite : public TransformationComponent {
public:
    void apply(glm::mat4 &matrix) override;

    void add(TransformationComponent *component);

    void clear() override;

private:
    std::vector<TransformationComponent *> components;
};

class Translate : public TransformationComponent {
public:
    explicit Translate(glm::vec3 vec);

    void apply(glm::mat4 &matrix) override;

private:
    glm::vec3 vec;
};

class Rotate : public TransformationComponent {
public:
    Rotate(float angle, glm::vec3 axis);

    void apply(glm::mat4 &matrix) override;

private:
    float angle;
    glm::vec3 axis;
};

class Scale : public TransformationComponent {
public:
    explicit Scale(glm::vec3 vec);

    void apply(glm::mat4 &matrix) override;

private:
    glm::vec3 vec;
};


class Transformation {
public:
    Transformation();

    glm::mat4 matrix;

    void add(TransformationComponent *component);

    void apply();

private:
    TransformationComposite composite;

};
