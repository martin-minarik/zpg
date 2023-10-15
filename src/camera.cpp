#include "camera.h"
#include "shader.h"

Camera::Camera() {
    calc_view_matrix();
}

void Camera::calc_view_matrix() {
    this->view_matrix = glm::lookAt(eye, eye + target, up);
}

void Camera::attach_shader(Shader *observer) {
    observers.push_back(observer);
}

void Camera::detach_shader(Shader *observer) {
    auto it = std::find(observers.begin(), observers.end(), observer);
    if (it != observers.end())
        observers.erase(it);
}

void Camera::notify_shader() {
    for (auto &observer: observers)
        observer->camera_update(this);
}

void Camera::process_mouse_movement(float diff_x, float diff_y, float delta_time) {
    alpha += diff_x * delta_time;
    fi += diff_y * delta_time;

    fi = std::max(0.f, std::min(fi, 90.f));

    if (fi < 0) {
        fi += 360.f;
    }

    printf("%.3f,  %.3f\n", alpha, fi);


    target.x = glm::sin(glm::radians(alpha)) * glm::cos(glm::radians(fi));
    target.z = glm::sin(glm::radians(alpha)) * glm::sin(glm::radians(fi));
    target.y = glm::cos(glm::radians(alpha));

    target = glm::normalize(target);

    calc_view_matrix();
    notify_shader();
}

void Camera::move_left(float delta_time) {
    eye += -( glm::normalize ( glm::cross( target , up ))) * (1.f * delta_time);
    calc_view_matrix();
    notify_shader();
}

void Camera::move_right(float delta_time) {
    eye += ( glm::normalize ( glm::cross( target , up ))) * (1.f * delta_time);
    calc_view_matrix();
    notify_shader();
}

void Camera::move_forward(float delta_time) {
    eye += glm::normalize(target) * 0.01f;
    calc_view_matrix();
    notify_shader();
}

void Camera::move_backward(float delta_time) {
    eye += -glm::normalize(target) * 0.01f;
    calc_view_matrix();
    notify_shader();
}


