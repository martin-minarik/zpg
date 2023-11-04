#include "application.h"

//
// Created by Martin Minarik
//

Application &Application::get_instance() {
    static Application instance;
    return instance;
}

Application::~Application() {
    delete scene;
}

void Application::run() {
    loop();
}

void Application::loop() {
    auto last_time = (float) glfwGetTime();
    while (!glfwWindowShouldClose(window)) {
        const auto now = (float) glfwGetTime();
        this->delta_time = now - last_time;
        last_time = now;

        // clear color and depth buffer
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        scene->update(delta_time);
        scene->draw();

        glfwPollEvents();
        glfwSwapBuffers(window);
    }

    glfwDestroyWindow(window);
    glfwTerminate();
    exit(EXIT_SUCCESS);
}


void Application::init() {
    init_opengl();
    init_callbacks();
}

void Application::init_opengl() {
    if (!glfwInit()) {
        fprintf(stderr, "ERROR: could not start GLFW3\n");
        exit(EXIT_FAILURE);
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    glfwWindowHint(GLFW_OPENGL_PROFILE,
                   GLFW_OPENGL_CORE_PROFILE);

    init_window();

    // start GLEW extension handler
    glewExperimental = GL_TRUE;
    glewInit();

    int width, height;
    glfwGetFramebufferSize(window, &width, &height);
    float ratio = width / (float) height;
    glViewport(0, 0, width, height);

    glEnable(GL_DEPTH_TEST);

    print_opengl_info();
}

void Application::init_window() {
    window = glfwCreateWindow(800, 600, "ZPG-MIN0139", nullptr, nullptr);
    if (!window) {
        glfwTerminate();
        exit(EXIT_FAILURE);
    }

    glfwMakeContextCurrent(window);
    glfwSwapInterval(1);
}

void Application::print_opengl_info() {
    printf("OpenGL Version: %s\n", glGetString(GL_VERSION));
    printf("Using GLEW %s\n", glewGetString(GLEW_VERSION));
    printf("Vendor %s\n", glGetString(GL_VENDOR));
    printf("Renderer %s\n", glGetString(GL_RENDERER));
    printf("GLSL %s\n", glGetString(GL_SHADING_LANGUAGE_VERSION));
    int major, minor, revision;
    glfwGetVersion(&major, &minor, &revision);
    printf("Using GLFW %i.%i.%i\n", major, minor, revision);
}

void Application::init_callbacks() {
    glfwSetErrorCallback(error_callback);
    MouseHandler &mouse_handler = MouseHandler::get_instance();
    mouse_handler.init_callbacks(this->window);

    KeyBoardHandler &keyboard_handler = KeyBoardHandler::get_instance();
    keyboard_handler.init_callbacks(this->window);
}

void Application::error_callback(int error, const char *description) { fputs(description, stderr); }

GLFWwindow *Application::get_window() const {
    return window;
}

float Application::get_delta_time() const {
    return delta_time;
}

void Application::set_scene(Scene *scene_) {
    if(this->scene)
        delete scene;
    this->scene = scene_;
    this->scene->init();
}











