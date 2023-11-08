#pragma once

//
// Created by Martin on 25.10.2023.
//


#include <vector>
#include <algorithm>

// Include Glew
#include "GL/glew.h"
// Include GLFW
#include "GLFW/glfw3.h"

// Include GLM
#include "glm/vec3.hpp" // glm::vec3
#include "glm/vec4.hpp" // glm::vec4
#include "glm/mat4x4.hpp" // glm::mat4
#include "glm/gtc/matrix_transform.hpp" // glm::translate, glm::rotate, glm::scale, glm::perspective
#include "glm/gtc/type_ptr.hpp" // glm::value_ptr

#include "transformation/placeable.h"
#include "observable.h"
#include "light/light.h"


class PointLight : public Light {
public:
    explicit PointLight(int id);

    [[nodiscard]] const glm::vec3 &get_position() const;

    void set_position(const glm::vec3 &position);

    [[nodiscard]] const Attenuation &get_attenuation() const;

    [[maybe_unused]] void set_attenuation(const Attenuation &attenuation_);

    void notify_observers() override;


private:
    glm::vec3 position{0, 0, 0};
    Attenuation attenuation = {1, 0, 0};
};
