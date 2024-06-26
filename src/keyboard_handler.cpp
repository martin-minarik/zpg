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
                Application::get_instance().set_scene(new SceneWeek9());
                break;

            case GLFW_KEY_2:
                Application::get_instance().set_scene(new SceneWeek9Night());
                break;

            case GLFW_KEY_3:
                Application::get_instance().set_scene(new Scene4Spheres());
                break;

            case GLFW_KEY_4:
                Application::get_instance().set_scene(new SceneSolarSystem());
                break;

            case GLFW_KEY_5:
                Application::get_instance().set_scene(new SceneTest3());
                break;

            case GLFW_KEY_6:
                Application::get_instance().set_scene(new SceneForest());
                break;

            case GLFW_KEY_T: {
                auto scene = Application::get_instance().get_current_scene();
                scene->interact_spawn_object(MouseHandler::get_instance().get_cursor_global_position());
            }
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

