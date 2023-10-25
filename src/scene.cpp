#include "scene.h"

Scene::Scene() {
    init();
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

    delete camera;
    delete point_light;
}

void Scene::init() {
    this->init_shader();
    this->init_camera();
    this->init_models();

    this->point_light = new PointLight();

    for (auto &item: shaders) {
        this->point_light->attach_observer(item.second);
    }

    this->scene2();

}

void Scene::init_shader() {
    this->shaders["constant"] = new Shader((char *) "resources\\shaders\\vertex.vert",
                                           (char *) "resources\\shaders\\constant.frag");

    this->shaders["lambert"] = new Shader((char *) "resources\\shaders\\vertex.vert",
                                          (char *) "resources\\shaders\\lambert.frag");

    this->shaders["phong"] = new Shader((char *) "resources\\shaders\\vertex.vert",
                                          (char *) "resources\\shaders\\phong.frag");

}

void Scene::init_models() {
    this->models["sphere"] = ModelFactory::create_by_name("sphere");
    this->models["suzie-flat"] = ModelFactory::create_by_name("suzie-flat");
    this->models["suzie-smooth"] = ModelFactory::create_by_name("suzie-smooth");
    this->models["cube"] = ModelFactory::create_by_name("cube");
}

void Scene::scene1() {
    for (auto &drawable_object: drawable_objects) {
        delete drawable_object;
    }
    this->point_light->set_translation(glm::vec3{0, 0, 0}, true);

    printf("const\n");
    this->drawable_objects.clear();
    drawable_objects.push_back(new DrawableObject(*models["sphere"], *shaders["lambert"]));
    drawable_objects[0]->set_translation(glm::vec3(0, 0, -2), false);
    drawable_objects[0]->set_scale(glm::vec3(1.5, 1.5, 1), false);


    for (auto &drawable_object: this->drawable_objects) {
        drawable_object->apply_transform();
    }
}

void Scene::scene2() {
    for (auto &drawable_object: drawable_objects) {
        delete drawable_object;
    }
    this->drawable_objects.clear();

    this->point_light->set_translation(glm::vec3{0.0, 0.0, -1.0}, true);

    printf("lambert\n");

    drawable_objects.push_back(new DrawableObject(*models["sphere"], *shaders["lambert"]));
    drawable_objects.push_back(new DrawableObject(*models["sphere"], *shaders["lambert"]));
    drawable_objects.push_back(new DrawableObject(*models["sphere"], *shaders["lambert"]));
    drawable_objects.push_back(new DrawableObject(*models["sphere"], *shaders["lambert"]));

    drawable_objects[0]->set_translation(glm::vec3(0, 2, -1), false);
    drawable_objects[1]->set_translation(glm::vec3(2, 0, -1), false);
    drawable_objects[2]->set_translation(glm::vec3(0, -2, -1), false);
    drawable_objects[3]->set_translation(glm::vec3(-2, 0, -1), false);

    for (auto &drawable_object: this->drawable_objects) {
        drawable_object->apply_transform();
    }
}

void Scene::scene3() {
    for (auto &drawable_object: drawable_objects) {
        delete drawable_object;
    }
    printf("Phong\n");

    this->point_light->set_translation(glm::vec3{0, 0, -1}, true);
    this->drawable_objects.clear();
    drawable_objects.push_back(new DrawableObject(*models["suzie-smooth"], *shaders["lambert"]));
    drawable_objects.push_back(new DrawableObject(*models["cube"], *shaders["constant"]));
    drawable_objects.push_back(new DrawableObject(*models["suzie-flat"], *shaders["phong"]));
    drawable_objects.push_back(new DrawableObject(*models["sphere"], *shaders["phong"]));

    drawable_objects[0]->set_translation(glm::vec3(0, 0.7, -2), false);
    drawable_objects[0]->set_scale(glm::vec3(0.7), false);
    drawable_objects[1]->set_translation(glm::vec3(1.4, 0, -1.5), false);
    drawable_objects[2]->set_translation(glm::vec3(0, -1.4, -1.5), false);
    drawable_objects[3]->set_translation(glm::vec3(-1.4, 0, -1.5), false);
    drawable_objects[3]->set_scale(glm::vec3(0.4), false);

    for (auto &drawable_object: this->drawable_objects) {
        drawable_object->apply_transform();
    }
}

void Scene::init_camera() {
    this->camera = new Camera();
    for (auto &item: shaders) {
        this->camera->attach_observer(item.second);
    }

    camera->notify_observers();
    MouseHandler::get_instance().set_camera(this->camera);
    KeyBoardHandler::get_instance().set_camera(this->camera);

    KeyBoardHandler::get_instance().set_scene(this);
}

void Scene::draw() {
    for (auto &drawable_object: drawable_objects)
        drawable_object->draw();
}

void Scene::update(float delta_time) {

}












