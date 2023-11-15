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

    for (auto &item: materials) {
        delete item.second;
        item.second = nullptr;
    }

    for (auto &light: lights) {
        delete light;
    }

    if (camera)
        delete camera;
}

void Scene::init() {
    this->init_shader();
    this->init_models();
    this->init_materials();
    this->init_light();
    this->init_camera();
    this->init_drawable_objects();
    this->init_skybox();
}

void Scene::draw() {
    this->draw_skybox();

    for (auto &drawable_object: drawable_objects)
        drawable_object->draw();
}

void Scene::draw_skybox() {
    glDepthMask(GL_FALSE);
    if (this->skybox)
        this->skybox->draw();
    glDepthMask(GL_TRUE);
}

void Scene::update(float delta_time) {

}














