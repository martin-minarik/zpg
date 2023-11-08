#pragma once

#include "glm/vec3.hpp" // glm::vec3
#include "glm/vec4.hpp" // glm::vec4
#include "glm/mat4x4.hpp" // glm::mat4
#include "glm/gtc/matrix_transform.hpp" // glm::translate, glm::rotate, glm::scale, glm::perspective
#include "glm/gtc/type_ptr.hpp" // glm::value_ptr

#include <observable.h>

class Material {
public:
    Material();

    explicit Material(const glm::vec4 &color);

    float get_ra() const;

    void set_ra(float ra);

    float get_rd() const;

    void set_rd(float rd);

    float get_rs() const;

    void set_rs(float rs);

    int get_specular_power() const;

    void set_specular_power(int specularPower);

    const glm::vec4 &get_color() const;

    void set_color(const glm::vec4 &color_);

    const glm::vec4 &get_ambient_color() const;

    void set_ambient_color(const glm::vec4 &ambientColor);

private:
    float r_a = 1;
    float r_d = 1;
    float r_s = 1;
    int specular_power = 32;
    glm::vec4 color{0.8, 0.8, 0.8, 1};
    glm::vec4 ambient_color{0.1, 0.1, 0.1, 1.0};
};
