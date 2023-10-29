#pragma once

//
// Created by Martin Minarik
//


#include <iostream>

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

// ZPG
#include "scenes/scene_4_spheres.h"
#include "scenes/scene_test_3.h"
#include "scenes/scene_solar_system.h"
#include "scenes/scene_forest.h"
#include "mouse_handler.h"
#include "keyboard_handler.h"

class Application {
public:
    virtual ~Application();

    static Application &get_instance();

    Application(const Application &) = delete;

    Application &operator=(const Application &) = delete;

    void run();

    [[nodiscard]] GLFWwindow *get_window() const;

    float get_delta_time() const;

private:
    Application() = default;

    void loop();

    void init();

    void init_opengl();

    void init_callbacks();

    void init_window();

    static void print_opengl_info();

    static void error_callback(int error, const char *description);

private:
    GLFWwindow *window = nullptr;
    Scene *scene;
    float delta_time = 0;
};

