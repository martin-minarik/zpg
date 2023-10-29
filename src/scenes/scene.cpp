#include "scenes/scene.h"

//
// Created by Martin Minarik
//

Scene::Scene() {
}

Scene::~Scene() {
    for (auto &drawable_object: drawable_objects) {
        delete drawable_object;
    }

    for (auto &item: models) {
        delete item.second;
        item.second = nullptr;
    }

    for (auto &item: shaders) {
        delete item.second;
        item.second = nullptr;
    }
    if (camera)
        delete camera;

    if (point_light)
        delete point_light;
}

void Scene::init() {
    this->init_shader();
    this->init_models();
    this->init_camera();
    this->init_light();
    this->init_drawable_objects();
}

void Scene::draw() {
    for (auto &drawable_object: drawable_objects)
        drawable_object->draw();
}

void Scene::update(float delta_time) {

}












