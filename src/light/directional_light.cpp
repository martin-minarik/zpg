#include "light/directional_light.h"

DirectionalLight::DirectionalLight(int id) : Light(id) {

}

void DirectionalLight::notify_observers() {
    Observable::notify_observers(LightClasses::DIRECTIONAL_LIGHT);
}

const glm::vec3 &DirectionalLight::get_direction() const {
    return direction;
}

void DirectionalLight::set_direction(const glm::vec3 &direction) {
    DirectionalLight::direction = direction;
    notify_observers();
}


