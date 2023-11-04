#pragma once

//
// Created by Martin Minarik
//

#include <iostream>

// Include Glew
#include "GL/glew.h"
// Include GLFW
#include "GLFW/glfw3.h"

#include "application.h"
#include "camera.h"

class MouseHandler {
public:
    static MouseHandler &get_instance();

    MouseHandler(const MouseHandler &) = delete;

    MouseHandler &operator=(const MouseHandler &) = delete;

    void init_callbacks(GLFWwindow *window);

    void set_camera(Camera *camera);

private:
    std::vector<int> pressed_buttons;
    Camera *camera = nullptr;

    MouseHandler() = default;

    void cursor_pos_callback(GLFWwindow *window, double current_x, double current_y);

    void mouse_button_callback(GLFWwindow *window, int button, int action, int mode);
};

