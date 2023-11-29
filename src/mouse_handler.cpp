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
    this->cursor_position_x = current_x;
    this->cursor_position_y = current_y;
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

}

void MouseHandler::mouse_button_callback(GLFWwindow *window, int button, int action, int mode) {
    if (action == GLFW_PRESS) {
        pressed_buttons.push_back(button);
        if (button == GLFW_MOUSE_BUTTON_1) {
            auto scene = Application::get_instance().get_current_scene();
            scene->interact_remove_object(this->get_cursor_object_index());
        }


    } else if (action == GLFW_RELEASE) {
        pressed_buttons.erase(std::remove(pressed_buttons.begin(),
                                          pressed_buttons.end(),
                                          button),
                              pressed_buttons.end());
    }
}

int MouseHandler::get_cursor_object_index() {
    auto window = Application::get_instance().get_window();

    GLuint index;

    GLint x = (GLint) this->cursor_position_x;
    GLint y = (GLint) this->cursor_position_y;

    int width, height;
    glfwGetFramebufferSize(window, &width, &height);
    int newy = height - y;
    glReadPixels(x, newy, 1, 1, GL_STENCIL_INDEX, GL_UNSIGNED_INT, &index);

    return index;
}

glm::vec3 MouseHandler::get_cursor_global_position() {
    auto window = Application::get_instance().get_window();

    GLfloat depth;
    GLint x = (GLint) this->cursor_position_x;
    GLint y = (GLint) this->cursor_position_y;

    int width, height;
    glfwGetFramebufferSize(window, &width, &height);
    int newy = height - y;

    glReadPixels(x, newy, 1, 1, GL_DEPTH_COMPONENT, GL_FLOAT, &depth);

    glm::vec3 screenX = glm::vec3{x, newy, depth};
    glm::vec4 viewport{0, 0, width, height};

    return glm::unProject(screenX, camera->view_matrix, camera->projection_matrix, viewport);
}
