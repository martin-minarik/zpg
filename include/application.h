#pragma once

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
#include "scene.h"
#include "mouse_handler.h"

class Application {
public:
    virtual ~Application();

    static Application &get_instance();

    Application(const Application &) = delete;

    Application &operator=(const Application &) = delete;

    void run();

    [[nodiscard]] GLFWwindow *get_window() const;

private:
    Application() = default;

    void loop();

    void init();

    void init_opengl();

    void init_callbacks();

    void init_window();

    static void print_opengl_info();

    static void error_callback(int error, const char *description);

    static void cursor_pos_callback(GLFWwindow *window, double mouseX, double mouseY);

private:
    GLFWwindow *window = nullptr;
    Scene *scene = nullptr;
};

