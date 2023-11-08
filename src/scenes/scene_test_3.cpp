//
// Created by Martin Minarik
//

#include "scenes/scene_test_3.h"


void SceneTest3::init_shader() {
    this->shaders["phong"] = new Shader((char *) "resources\\shaders\\vertex.vert",
                                        (char *) "resources\\shaders\\phong.frag");
    this->shaders["phong2"] = new Shader((char *) "resources\\shaders\\vertex.vert",
                                        (char *) "resources\\shaders\\phong2.frag");
}

void SceneTest3::init_materials() {
    this->materials["base_material"] = new Material();
    this->materials["base_material"]->set_specular_power(1.0);
}

void SceneTest3::init_camera() {
    this->camera = new Camera();
    for (auto &item: shaders) {
        this->camera->attach_observer(item.second);
    }

    camera->notify_observers();
    MouseHandler::get_instance().set_camera(this->camera);
    KeyBoardHandler::get_instance().set_camera(this->camera);
}

void SceneTest3::init_models() {
    this->models["sphere"] = ModelFactory::create_by_name("sphere");
}

void SceneTest3::init_light() {
    this->point_light = new PointLight(0);

    for (auto &item: shaders) {
        this->point_light->attach_observer(item.second);
    }

    this->point_light->set_position(glm::vec3{0.0, 0.0, -1.5});
}

void SceneTest3::init_drawable_objects() {
    drawable_objects.push_back(new DrawableObject(*models["sphere"], *shaders["phong"], *materials["base_material"]));

    drawable_objects[0]->add_translation(glm::vec3(0, 0, 0), false);


    for (auto &drawable_object: this->drawable_objects) {
        drawable_object->apply_transform();
    }
}



