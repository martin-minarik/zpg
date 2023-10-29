//
// Created by Martin Minarik
//

#include "scenes/scene_solar_system.h"

void SceneSolarSystem::init_shader() {
    this->shaders["constant"] = new Shader((char *) "resources\\shaders\\vertex.vert",
                                           (char *) "resources\\shaders\\constant.frag");

    this->shaders["lambert"] = new Shader((char *) "resources\\shaders\\vertex.vert",
                                          (char *) "resources\\shaders\\lambert.frag");

    this->shaders["phong"] = new Shader((char *) "resources\\shaders\\vertex.vert",
                                        (char *) "resources\\shaders\\phong.frag");
    this->shaders["blinn"] = new Shader((char *) "resources\\shaders\\vertex.vert",
                                        (char *) "resources\\shaders\\blinn.frag");
}

void SceneSolarSystem::init_camera() {
    this->camera = new Camera();
    for (auto &item: shaders) {
        this->camera->attach_observer(item.second);
    }

    camera->notify_observers();
    MouseHandler::get_instance().set_camera(this->camera);
    KeyBoardHandler::get_instance().set_camera(this->camera);
}

void SceneSolarSystem::init_models() {
    this->models["sphere"] = ModelFactory::create_by_name("sphere");
    this->models["suzie-flat"] = ModelFactory::create_by_name("suzie-flat");
    this->models["suzie-smooth"] = ModelFactory::create_by_name("suzie-smooth");
    this->models["cube"] = ModelFactory::create_by_name("cube");
}

void SceneSolarSystem::init_light() {
    this->point_light = new PointLight();

    for (auto &item: shaders) {
        this->point_light->attach_observer(item.second);
    }

    this->point_light->set_translation(glm::vec3{0.0, 0.0, -1.0}, true);
}

void SceneSolarSystem::init_drawable_objects() {
    auto *sun = new DrawableObject(*models["sphere"], *shaders["blinn"]);
    auto *mercury = new DrawableObject(*models["sphere"], *shaders["blinn"]);
    auto *mercury_moon = new DrawableObject(*models["sphere"], *shaders["blinn"]);



    drawable_objects.push_back(sun);
    drawable_objects.push_back(mercury);
    drawable_objects.push_back(mercury_moon);

    sun->set_translation(glm::vec3(0, 0, 0), false);
    mercury->set_translation(glm::vec3(0, 0, -2), false);
    mercury->set_scale(glm::vec3(0.2), false);
    mercury_moon->set_translation(glm::vec3(0, 0, -2.5), false);
    mercury_moon->set_scale(glm::vec3(0.07), false);


    for (auto &drawable_object: this->drawable_objects) {
        drawable_object->apply_transform();
    }
}
