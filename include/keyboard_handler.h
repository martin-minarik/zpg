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
#include "scenes/scene_4_spheres.h"
#include "scenes/scene_forest.h"
#include "scenes/scene_test_3.h"
#include "scenes/scene_solar_system.h"
#include "scenes/scene_week_9.h"
#include "scenes/scene_week_9_night.h"

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

