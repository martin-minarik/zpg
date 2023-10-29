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
#include "vector"


class KeyBoardHandler {
public:

    static KeyBoardHandler &get_instance();

    KeyBoardHandler(const KeyBoardHandler &) = delete;

    KeyBoardHandler &operator=(const KeyBoardHandler &) = delete;

    void init_callbacks(GLFWwindow *window);

    void set_camera(Camera *camera);


private:
    Camera *camera = nullptr;
    std::vector<int> pressed_keys;

    KeyBoardHandler() = default;

    void key_callback(GLFWwindow *window, int key, int scancode, int action, int mods);
};

