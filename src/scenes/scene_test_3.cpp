//
// Created by Martin Minarik
//

#include "scenes/scene_test_3.h"


void SceneTest3::init_shader() {
    this->shaders["phong"] = new Shader((char *) "resources\\shaders\\vertex.vert",
                                        (char *) "resources\\shaders\\phong.frag");
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
    {
        PointLight *light = new PointLight(0);
        light->set_position(glm::vec3{0.0, 0.0, 0.0});
        this->lights.push_back(light);
    }



    for (auto &item: shaders) {
        for (auto &light: lights) {
            light->attach_observer(item.second);
        }

        item.second->upload_number_of_lights(this->lights.size());
    }

    for (auto &light: lights) {
        light->notify_observers();
    }
}

void SceneTest3::init_drawable_objects() {
    drawable_objects.push_back(new DrawableObject(*models["sphere"], *shaders["phong"], *materials["base_material"]));

    drawable_objects[0]->add_translation(glm::vec3(0, 0, 0), false);


    for (auto &drawable_object: this->drawable_objects) {
        drawable_object->apply_transform();
    }
}



