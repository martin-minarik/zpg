//
// Created by Martin Minarik
//

#include "scenes/scene_4_spheres.h"


void Scene4Spheres::init_shader() {
//    this->shaders["constant"] = new Shader((char *) "resources\\shaders\\vertex.vert",
//                                           (char *) "resources\\shaders\\constant.frag");

    this->shaders["lambert"] = new Shader((char *) "resources\\shaders\\vertex.vert",
                                          (char *) "resources\\shaders\\lambert.frag");

//    this->shaders["phong"] = new Shader((char *) "resources\\shaders\\vertex.vert",
//                                        (char *) "resources\\shaders\\phong.frag");
//
//    this->shaders["blinn"] = new Shader((char *) "resources\\shaders\\vertex.vert",
//                                        (char *) "resources\\shaders\\blinn.frag");
}

void Scene4Spheres::init_materials() {
    this->materials["material1"] = new Material();
    this->materials["material2"] = new Material();
    this->materials["material3"] = new Material();
    this->materials["material4"] = new Material();

    this->materials["material1"]->set_specular_power(100);

    this->materials["material2"]->set_specular_power(32);

    this->materials["material3"]->set_specular_power(32);

    this->materials["material4"]->set_specular_power(32);

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
}

void Scene4Spheres::init_light() {
    this->point_light = new PointLight();

    for (auto &item: shaders) {
        this->point_light->attach_observer(item.second);
    }

    this->point_light->set_position(glm::vec3{0.0, 0.0, 0.0});
}

void Scene4Spheres::init_drawable_objects() {
    drawable_objects.push_back(new DrawableObject(*models["sphere"], *shaders["lambert"], *materials["material1"]));
    drawable_objects.push_back(new DrawableObject(*models["sphere"], *shaders["lambert"], *materials["material2"]));
    drawable_objects.push_back(new DrawableObject(*models["sphere"], *shaders["lambert"], *materials["material3"]));
    drawable_objects.push_back(new DrawableObject(*models["sphere"], *shaders["lambert"], *materials["material4"]));

    drawable_objects[0]->add_translation(glm::vec3(2, 0, 0), false);
    drawable_objects[1]->add_translation(glm::vec3(0, 2, 0), false);
    drawable_objects[2]->add_translation(glm::vec3(-2, 0, 0), false);
    drawable_objects[3]->add_translation(glm::vec3(0, -2, 0), false);

    for (auto &drawable_object: this->drawable_objects) {
        drawable_object->apply_transform();
    }
}


