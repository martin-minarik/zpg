#include "keyboard_handler.h"

//
// Created by Martin Minarik
//

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
    if (action == GLFW_PRESS) {
        switch (key) {
            case GLFW_KEY_1:
                if (scene)
                    scene->scene1();
                break;

            case GLFW_KEY_2:
                if (scene)
                    scene->scene2();
                break;

            case GLFW_KEY_3:
                if (scene)
                    scene->scene3();
                break;

            default:
                pressed_keys.push_back(key);
                break;
        }
    } else if (action == GLFW_RELEASE) {
        pressed_keys.erase(std::remove(pressed_keys.begin(),
                                       pressed_keys.end(),
                                       key),
                           pressed_keys.end());
    }


    if (!pressed_keys.empty()) {
        for (auto pressed_key: pressed_keys) {
            switch (pressed_key) {
                case GLFW_KEY_W:
                    if (camera)
                        camera->move_forward(delta_time);
                    break;
                case GLFW_KEY_S:
                    if (camera)
                        camera->move_backward(delta_time);
                    break;

                case GLFW_KEY_A:
                    if (camera)
                        camera->move_left(delta_time);
                    break;

                case GLFW_KEY_D:
                    if (camera)
                        camera->move_right(delta_time);
                    break;

                default:
                    break;
            }
        }

    }
}

void KeyBoardHandler::set_camera(Camera *camera) {
    KeyBoardHandler::camera = camera;
}

void KeyBoardHandler::set_scene(Scene *scene) {
    KeyBoardHandler::scene = scene;
}
