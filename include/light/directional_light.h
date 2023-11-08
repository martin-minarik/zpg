#pragma once

// Include GLM
#include "glm/vec3.hpp" // glm::vec3
#include "glm/vec4.hpp" // glm::vec4
#include "glm/mat4x4.hpp" // glm::mat4
#include "glm/gtc/matrix_transform.hpp" // glm::translate, glm::rotate, glm::scale, glm::perspective
#include "glm/gtc/type_ptr.hpp" // glm::value_ptr

#include "transformation/placeable.h"
#include "light/light.h"

class DirectionalLight : public Light{
public:
    explicit DirectionalLight(int id);

    const glm::vec3 &get_direction() const;

    void set_direction(const glm::vec3 &direction);

    void notify_observers() override;

private:
    glm::vec3 direction{0,1,0};
};
