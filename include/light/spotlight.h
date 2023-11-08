#pragma once

// Include GLM
#include "glm/vec3.hpp" // glm::vec3
#include "glm/vec4.hpp" // glm::vec4
#include "glm/mat4x4.hpp" // glm::mat4
#include "glm/gtc/matrix_transform.hpp" // glm::translate, glm::rotate, glm::scale, glm::perspective
#include "glm/gtc/type_ptr.hpp" // glm::value_ptr

#include "transformation/placeable.h"
#include "light/light.h"
#include "camera.h"


class Spotlight : public Light, public Observer<Camera>{
public:
    explicit Spotlight(int id);

    void notify_observers() override;

    const glm::vec3 &get_position() const;

    void set_position(const glm::vec3 &position);

    const glm::vec3 &get_direction() const;

    void set_direction(const glm::vec3 &direction);

    const Attenuation &get_attenuation() const;

    void set_attenuation(const Attenuation &attenuation);

    float get_cut_off() const;

    void set_cut_off(float cutOff);

    void update(Camera *camera) override;

private:
    glm::vec3 position{0, 0, 2};
    glm::vec3 direction{0,0,-1};
    float cut_off = glm::cos(glm::radians(12.5f));
    Attenuation attenuation = {1, 0, 0};
};
