#include "mouse_handler.h"

MouseHandler &MouseHandler::get_instance() {
    static MouseHandler instance;
    return instance;
}

void MouseHandler::init_callbacks(GLFWwindow *window) {
    glfwSetCursorPosCallback(window, [](GLFWwindow *window, double mouseXPos, double mouseYPos) -> void {
        MouseHandler::get_instance().cursor_pos_callback(window, mouseXPos, mouseYPos);
    });
}

void MouseHandler::cursor_pos_callback(GLFWwindow *window, double current_x, double current_y) {
    if (this->first_move) {
        last_x = current_x;
        last_y = current_y;
        first_move = false;
    } else {
        float x_diff = current_x - last_x;
        float y_diff = current_y - last_y;
        auto delta_time = Application::get_instance().get_delta_time();

        last_x = current_x;
        last_y = current_y;

        if (camera)
            camera->process_mouse_movement(x_diff, y_diff, delta_time);
    }
}

void MouseHandler::set_camera(Camera *camera) {
    MouseHandler::camera = camera;
}
