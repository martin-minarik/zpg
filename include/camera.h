#pragma once

//
// Created by Martin Minarik
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
#include "observable.h"


class Camera : public Observable<Camera> {
public:
    Camera();

    void calc_view_matrix();

    void calc_projection_matrix(float fov, float ratio, float near, float far);

    void process_mouse_movement(float diff_x, float diff_y, float delta_time);

    void move_left(float delta_time);

    void move_right(float delta_time);

    void move_forward(float delta_time);

    void move_backward(float delta_time);

    glm::mat4 projection_matrix = glm::mat4{1.f};
    glm::mat4 view_matrix = glm::mat4{1.f};

    const glm::vec3 &get_eye() const;

    void set_eye(const glm::vec3 &eye);

    const glm::vec3 &get_target() const;

    void set_target(const glm::vec3 &target);


private:
    float alpha = 0.f;
    float fi = 0.f;
    float mouse_speed = 30;
    glm::vec3 eye{0.f, 0.f, 5.f};
    glm::vec3 target{0.0f, 0.f, -1.f};
    glm::vec3 up{0.f, 1.f, 0.f};
};
