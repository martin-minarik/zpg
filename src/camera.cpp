#include "camera.h"

//
// Created by Martin Minarik
//

Camera::Camera() {
    calc_view_matrix();
    calc_projection_matrix(60.f, 4.0 / 3.0, 0.1f, 100.f);
}

void Camera::calc_view_matrix() {
    this->view_matrix = glm::lookAt(eye, eye + target, up);
}

void Camera::calc_projection_matrix(float fov, float ratio, float z_near, float z_far) {
    projection_matrix = glm::perspective(glm::radians(fov), ratio, z_near, z_far);
    notify_observers();
}


void Camera::process_mouse_movement(float diff_x, float diff_y, float delta_time) {
    alpha += diff_x * delta_time * this->mouse_speed;
    fi += -diff_y * delta_time * this->mouse_speed;

    if (fi > 90.0f)
        fi = 90.0f;
    if (fi < -90.0f)
        fi = -90.0f;

    target.x = glm::cos(glm::radians(alpha)) * glm::cos(glm::radians(fi));
    target.y = glm::sin(glm::radians(fi));
    target.z = glm::sin(glm::radians(alpha)) * glm::cos(glm::radians(fi));

    target = glm::normalize(target);

    calc_view_matrix();
    notify_observers();
}

void Camera::move_left(float delta_time) {
    eye += -(glm::normalize(glm::cross(target, up))) * 5.f * delta_time;
    calc_view_matrix();
    notify_observers();
}

void Camera::move_right(float delta_time) {
    eye += (glm::normalize(glm::cross(target, up))) * 5.f * delta_time;
    calc_view_matrix();
    notify_observers();
}

void Camera::move_forward(float delta_time) {
    eye += glm::normalize(target) * 5.f * delta_time;
    calc_view_matrix();
    notify_observers();
}

void Camera::move_backward(float delta_time) {
    eye += -glm::normalize(target) * 5.f * delta_time;
    calc_view_matrix();
    notify_observers();
}

const glm::vec3 &Camera::get_eye() const {
    return eye;
}

void Camera::set_eye(const glm::vec3 &eye) {
    Camera::eye = eye;
    calc_view_matrix();
}

const glm::vec3 &Camera::get_target() const {
    return target;
}

void Camera::set_target(const glm::vec3 &target) {
    Camera::target = target;
    calc_view_matrix();
}



