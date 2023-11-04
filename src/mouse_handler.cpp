#include "mouse_handler.h"

//
// Created by Martin Minarik
//

MouseHandler &MouseHandler::get_instance() {
    static MouseHandler instance;
    return instance;
}

void MouseHandler::set_camera(Camera *camera) {
    MouseHandler::camera = camera;
}

void MouseHandler::init_callbacks(GLFWwindow *window) {
    glfwSetCursorPosCallback(window, [](GLFWwindow *window, double mouseXPos, double mouseYPos) -> void {
        MouseHandler::get_instance().cursor_pos_callback(window, mouseXPos, mouseYPos);
    });

    glfwSetMouseButtonCallback(window, [](GLFWwindow *window, int button, int action, int mode) -> void {
        MouseHandler::get_instance().mouse_button_callback(window, button, action, mode);
    });

    glfwSetWindowSizeCallback(window, [](GLFWwindow *window, int width, int height) {
        auto ratio = (float) width / (float) height;
        printf("%d x %d, %.3f\n", width, height, ratio);

        glViewport(0, 0, width, height);
        MouseHandler::get_instance().camera->calc_projection_matrix(60.f, ratio, 0.1f, 100.f);
    });
}

void MouseHandler::cursor_pos_callback(GLFWwindow *window, double current_x, double current_y) {
    static double last_x = current_x;
    static double last_y = current_y;
    float x_diff = current_x - last_x;
    float y_diff = current_y - last_y;
    auto delta_time = Application::get_instance().get_delta_time();

    last_x = current_x;
    last_y = current_y;

    if (camera)
        if (std::find(pressed_buttons.begin(), pressed_buttons.end(), GLFW_MOUSE_BUTTON_2)
            != pressed_buttons.end()) {
            camera->process_mouse_movement(x_diff, y_diff, delta_time);
        }
//    }
}

void MouseHandler::mouse_button_callback(GLFWwindow *window, int button, int action, int mode) {
    if (action == GLFW_PRESS) {
        pressed_buttons.push_back(button);

    } else if (action == GLFW_RELEASE) {
        pressed_buttons.erase(std::remove(pressed_buttons.begin(),
                                          pressed_buttons.end(),
                                          button),
                              pressed_buttons.end());
    }


}
