#include "scene.h"

Scene::Scene() {
    init();
}

Scene::~Scene() {
    delete camera;

    for (auto &drawable_object: drawable_objects) {
        delete drawable_object;
    }

    for (auto &model: models) {
        delete model;
    }

    for (auto &item: shaders) {
        delete item.second;
        item.second = nullptr;
    }
}

void Scene::init() {
    this->init_shader();
    this->init_drawable_objects();
    this->init_camera();
    this->init_transformations();
}

void Scene::init_shader() {
    this->shaders["vertex_color"] = new Shader((char *) "resources\\shaders\\vertex.vert",
                                               (char *) "resources\\shaders\\color.frag");

}

void Scene::init_drawable_objects() {
    Model *cube_model = ModelFactory::create_by_name("cube");
    Model *sphere_model = ModelFactory::create_by_name("sphere");
    Model *suzie_flat = ModelFactory::create_by_name("suzie-flat");
    Model *suzie_smooth = ModelFactory::create_by_name("suzie-smooth");
    this->models.push_back(cube_model);
    this->models.push_back(sphere_model);
    this->models.push_back(suzie_flat);
    this->models.push_back(suzie_smooth);

    drawable_objects.push_back(new DrawableObject(*suzie_flat, *shaders["vertex_color"]));
    drawable_objects.push_back(new DrawableObject(*cube_model, *shaders["vertex_color"]));
    drawable_objects.push_back(new DrawableObject(*suzie_flat, *shaders["vertex_color"]));
    drawable_objects.push_back(new DrawableObject(*sphere_model, *shaders["vertex_color"]));
    drawable_objects.push_back(new DrawableObject(*sphere_model, *shaders["vertex_color"]));
    drawable_objects.push_back(new DrawableObject(*suzie_smooth, *shaders["vertex_color"]));
    drawable_objects.push_back(new DrawableObject(*suzie_flat, *shaders["vertex_color"]));
}

void Scene::init_transformations() {
    this->rotation.reset(new Rotation(0, glm::vec3(0, 1, 0)));

    drawable_objects[0]->add_transform(rotation, false);
    drawable_objects[0]->set_rotation(180, glm::vec3(0, 0, 1), false);
    drawable_objects[0]->set_scale(glm::vec3(0.3, 0.3, 0.3), false);


    drawable_objects[1]->set_translation(glm::vec3(0, 0, -5), false);
    drawable_objects[1]->set_rotation(180, glm::vec3(0, 0, 1), false);
    drawable_objects[1]->add_transform(rotation, false);


    drawable_objects[2]->set_translation(glm::vec3(2, 2, -2), false);


    drawable_objects[3]->set_translation(glm::vec3(-2, 2, -2), false);
    drawable_objects[3]->set_scale(glm::vec3(0.3), false);


    drawable_objects[4]->set_translation(glm::vec3(2, -2, -2), false);


    drawable_objects[5]->set_translation(glm::vec3(-2, -2, -2), false);


    drawable_objects[6]->set_translation(glm::vec3(0, 0, -2), false);
    drawable_objects[6]->set_scale(glm::vec3(0.3, 0.3, 0.3), false);
//
    for (auto &drawable_object: this->drawable_objects) {
        drawable_object->apply_transform();
    }
}

void Scene::init_camera() {
    this->camera = new Camera();
    if (camera) {
        for (auto &item: shaders) {
            this->camera->attach_observer(item.second);
        }

        camera->notify_observers();
        MouseHandler::get_instance().set_camera(this->camera);
        KeyBoardHandler::get_instance().set_camera(this->camera);
    }
}

void Scene::draw() {
    for (auto &drawable_object: drawable_objects)
        drawable_object->draw();
}

void Scene::update(float delta_time) {
    rotation->set_angle(rotation->get_angle() + 50 * delta_time);
    for (auto &drawable_object: this->drawable_objects)
        drawable_object->apply_transform();
}






