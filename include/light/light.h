#pragma once

//
// Created by Martin Minarik
//

// Include GLM
#include "glm/vec3.hpp" // glm::vec3
#include "glm/vec4.hpp" // glm::vec4
#include "glm/mat4x4.hpp" // glm::mat4
#include "glm/gtc/matrix_transform.hpp" // glm::translate, glm::rotate, glm::scale, glm::perspective
#include "glm/gtc/type_ptr.hpp" // glm::value_ptr

#include "transformation/placeable.h"
#include "observable.h"

struct Attenuation {
    float k_constant;
    float k_linear;
    float k_quadratic;
};

enum LightClasses {
    LIGHT_BASE,
    POINT_LIGHT,
    DIRECTIONAL_LIGHT,
    SPOT_LIGHT
};

class Light : public Observable<Light> {
public:
    explicit Light(int id);

    [[nodiscard]] const glm::vec3 &get_color() const;

    void set_color(const glm::vec3 &color);

    int get_id() const;

    virtual void notify_observers() override;

private:
    int id;
    glm::vec3 color{1, 1, 1};
};
