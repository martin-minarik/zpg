//
// Created by Martin Minarik
//

#include "scenes/scene_4_spheres.h"


void Scene4Spheres::init_shader() {
    this->shaders["constant"] = new Shader((char *) "resources\\shaders\\vertex.vert",
                                           (char *) "resources\\shaders\\constant.frag");

    this->shaders["lambert"] = new Shader((char *) "resources\\shaders\\vertex.vert",
                                          (char *) "resources\\shaders\\lambert.frag");

    this->shaders["phong"] = new Shader((char *) "resources\\shaders\\vertex.vert",
                                        (char *) "resources\\shaders\\phong.frag");
    this->shaders["blinn"] = new Shader((char *) "resources\\shaders\\vertex.vert",
                                        (char *) "resources\\shaders\\blinn.frag");
}

void Scene4Spheres::init_camera() {
    this->camera = new Camera();
    for (auto &item: shaders) {
        this->camera->attach_observer(item.second);
    }

    camera->notify_observers();
    MouseHandler::get_instance().set_camera(this->camera);
    KeyBoardHandler::get_instance().set_camera(this->camera);
}

void Scene4Spheres::init_models() {
    this->models["sphere"] = ModelFactory::create_by_name("sphere");
    this->models["suzie-flat"] = ModelFactory::create_by_name("suzie-flat");
    this->models["suzie-smooth"] = ModelFactory::create_by_name("suzie-smooth");
    this->models["cube"] = ModelFactory::create_by_name("cube");
}

void Scene4Spheres::init_light() {
    this->point_light = new PointLight();

    for (auto &item: shaders) {
        this->point_light->attach_observer(item.second);
    }

    this->point_light->set_translation(glm::vec3{0.0, 0.0, -1.0}, true);
}

void Scene4Spheres::init_drawable_objects() {
    drawable_objects.push_back(new DrawableObject(*models["sphere"], *shaders["blinn"]));
    drawable_objects.push_back(new DrawableObject(*models["sphere"], *shaders["blinn"]));
    drawable_objects.push_back(new DrawableObject(*models["sphere"], *shaders["blinn"]));
    drawable_objects.push_back(new DrawableObject(*models["sphere"], *shaders["blinn"]));

    drawable_objects[0]->set_translation(glm::vec3(2, 0, 0), false);
    drawable_objects[1]->set_translation(glm::vec3(-2, 0, 0), false);
    drawable_objects[2]->set_translation(glm::vec3(0, 2, 0), false);
    drawable_objects[3]->set_translation(glm::vec3(0, -2, 0), false);

    for (auto &drawable_object: this->drawable_objects) {
        drawable_object->apply_transform();
    }
}

