#include "keyboard_handler.h"

KeyBoardHandler &KeyBoardHandler::get_instance() {
    static KeyBoardHandler instance;
    return instance;
}

void KeyBoardHandler::init_callbacks(GLFWwindow *window) {
    glfwSetKeyCallback(window, [](GLFWwindow *window, int key, int scancode, int action, int mods) -> void {
        KeyBoardHandler::get_instance().key_callback(window, key, scancode, action, mods);
    });
}

void KeyBoardHandler::key_callback(GLFWwindow *window, int key, int scancode, int action, int mods) {
    auto delta_time = Application::get_instance().get_delta_time();
    switch (key) {
        case GLFW_KEY_W:
            if(camera)
                camera->move_forward(delta_time);
            break;

        case GLFW_KEY_S:
            if(camera)
                camera->move_backward(delta_time);
            break;

        case GLFW_KEY_A:
            if(camera)
                camera->move_left(delta_time);
            break;

        case GLFW_KEY_D:
            if(camera)
                camera->move_right(delta_time);
            break;
    }
}

void KeyBoardHandler::set_camera(Camera *camera) {
    KeyBoardHandler::camera = camera;
}
