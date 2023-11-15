#include "scenes/scene_solar_system.h"

//
// Created by Martin Minarik
//

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

void SceneSolarSystem::init_materials() {
    this->materials["sun_material"] = new Material(glm::vec4{1, 0.6, 0, 1});
    this->materials["mercury"] = new Material(glm::vec4{0.7, 0.7, 0.4, 1});
    this->materials["earth"] = new Material(glm::vec4{0, 1, 0.5, 1});
    this->materials["moon"] = new Material(glm::vec4{0.8, 0.8, 0.8, 1});
}

void SceneSolarSystem::init_light() {
    {
        auto *light = new PointLight(this->lights.size());
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

void SceneSolarSystem::init_drawable_objects() {
    auto *sun = new DrawableObject(*models["sphere"], *shaders["constant"], *materials["sun_material"]);
    auto *mercury = new DrawableObject(*models["sphere"], *shaders["phong"], *materials["mercury"]);
    auto *mercury_moon = new DrawableObject(*models["sphere"], *shaders["lambert"], *materials["mercury"]);
    auto *earth = new DrawableObject(*models["sphere"], *shaders["blinn"], *materials["earth"]);
    auto *earth_moon = new DrawableObject(*models["sphere"], *shaders["lambert"], *materials["moon"]);

    drawable_objects.push_back(sun);
    drawable_objects.push_back(mercury);
    drawable_objects.push_back(mercury_moon);
    drawable_objects.push_back(earth);
    drawable_objects.push_back(earth_moon);

    sun_rotation = std::make_shared<Rotation>(0, glm::vec3{0, 0, 1});
    moon_rotation = std::make_shared<Rotation>(0, glm::vec3{0, 0, 1});

    sun->add_transform(sun_rotation, false);
    sun->add_scale(glm::vec3{0.5}, false);

    auto mercury_orbit = std::make_shared<TransformationComposite>();
    mercury_orbit->add(sun_rotation);
    mercury_orbit->add_translation(glm::vec3(0, -1.5, 0));

    mercury->add_transform(mercury_orbit, false);
    mercury->add_scale(glm::vec3(0.13), false);

    mercury_moon->add_transform(mercury_orbit, false);
    mercury_moon->add_transform(moon_rotation);
    mercury_moon->add_translation(glm::vec3(0, 0.35, 0));
    mercury_moon->add_scale(glm::vec3(0.04), false);

    auto earth_orbit = std::make_shared<TransformationComposite>();
    earth_orbit->add(sun_rotation);
    earth_orbit->add_translation(glm::vec3(2.5, 0, 0));

    earth->add_transform(earth_orbit, false);
    earth->add_scale(glm::vec3(0.22), false);

    earth_moon->add_transform(earth_orbit, false);
    earth_moon->add_transform(moon_rotation);
    earth_moon->add_translation(glm::vec3(0, 0.4, 0));
    earth_moon->add_scale(glm::vec3(0.04), false);


    for (auto &drawable_object: this->drawable_objects) {
        drawable_object->apply_transform();
    }
}

void SceneSolarSystem::update(float delta_time) {
    sun_rotation->set_angle(sun_rotation->get_angle() + 20 * delta_time);
    moon_rotation->set_angle(moon_rotation->get_angle() + 80 * delta_time);
    for (auto &drawable_object: this->drawable_objects) {
        drawable_object->apply_transform();
    }
}

void SceneSolarSystem::init_skybox() {

}
