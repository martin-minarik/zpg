#include "scenes/scene_forest.h"

//
// Created by Martin Minarik
//

void SceneForest::init_shader() {
    this->shaders["constant"] = new Shader((char *) "resources\\shaders\\vertex.vert",
                                           (char *) "resources\\shaders\\constant.frag");
    this->shaders["lambert"] = new Shader((char *) "resources\\shaders\\vertex.vert",
                                          (char *) "resources\\shaders\\lambert.frag");
    this->shaders["phong"] = new Shader((char *) "resources\\shaders\\vertex.vert",
                                        (char *) "resources\\shaders\\phong.frag");

    this->shaders["blinn"] = new Shader((char *) "resources\\shaders\\vertex.vert",
                                        (char *) "resources\\shaders\\blinn.frag");

    this->shaders["skybox"] = new Shader((char *) "resources\\shaders\\skybox.vert",
                                         (char *) "resources\\shaders\\skybox.frag");
}

void SceneForest::init_materials() {
    this->materials["plain"] = new Material(glm::vec4{0.2, 0.75, 0.2, 1});
    this->materials["tree"] = new Material(glm::vec4{0.6, 0.5, 0.9, 1});
    this->materials["bush"] = new Material(glm::vec4{0.9, 0.2, 0.7, 1});
    this->materials["sphere"] = new Material(glm::vec4{0.5, 0.7, 0.9, 1});
    this->materials["suzie"] = new Material(glm::vec4{0.9, 0.2, 0.2, 1});
    this->materials["gift"] = new Material(glm::vec4{0.9, 0.9, 0.0, 1});


    auto grass_material = new Material();
    auto texture = std::make_shared<Texture>("resources\\textures\\grass.png");
    grass_material->set_texture(texture);
    grass_material->set_texture_resolution(20);
    this->materials["grass_material"] = grass_material;

}

void SceneForest::init_camera() {
    this->camera = new Camera();

    for (auto &item: shaders) {
        this->camera->attach_observer(item.second);
    }

    camera->set_eye(glm::vec3{0, 2, 2});

    camera->notify_observers();
    MouseHandler::get_instance().set_camera(this->camera);
    KeyBoardHandler::get_instance().set_camera(this->camera);
}

void SceneForest::init_models() {
    this->models["plain"] = ModelFactory::create_by_name("plain");
    this->models["tree"] = ModelFactory::create_by_name("tree");
    this->models["bush"] = ModelFactory::create_by_name("bushes");
    this->models["sphere"] = ModelFactory::create_by_name("sphere");
    this->models["suzie-flat"] = ModelFactory::create_by_name("suzie-flat");
    this->models["suzie-smooth"] = ModelFactory::create_by_name("suzie-flat");
    this->models["gift"] = ModelFactory::create_by_name("gift");
    this->models["uv_plain"] = ModelFactory::create_by_name("uv_plain");
}

void SceneForest::init_light() {
    {
        auto *light = new PointLight(this->lights.size());
        light->set_position(glm::vec3{0.0, 3.0, 2.0});
        light->set_attenuation({1, 0.1, 1});
        this->lights.push_back(light);
    }

    {
        auto *light = new DirectionalLight(this->lights.size());
        light->set_direction(glm::vec3{-1.0, 1.0, 1.0});
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

void SceneForest::init_drawable_objects() {
    auto grass = new DrawableObject(*models["uv_plain"], *shaders["constant"], *materials["grass_material"]);
    grass->add_scale(glm::vec3(100, 1, 100), false);
    drawable_objects.push_back(grass);

    auto suzie = new DrawableObject(*models["suzie-smooth"], *shaders["phong"], *materials["suzie"]);
    suzie->add_translation(glm::vec3(0, 1, 2), false);
    suzie->add_scale(glm::vec3(0.5), false);
    drawable_objects.push_back(suzie);

    auto gift_ = new DrawableObject(*models["gift"], *shaders["phong"], *materials["gift"]);
    gift_->add_translation(glm::vec3(3, 1, 2), false);
    gift_->add_scale(glm::vec3(3), false);
    drawable_objects.push_back(gift_);

    auto sphere_ = new DrawableObject(*models["sphere"], *shaders["blinn"], *materials["sphere"]);
    sphere_->add_translation(glm::vec3(-3, 1, 2), false);
    sphere_->add_scale(glm::vec3(0.5), false);
    drawable_objects.push_back(sphere_);

    for (int i = 0; i < 70; ++i) {
        auto random_x = (rand() % (24 - 0 + 1) + 0) - 12;
        auto random_z = -(rand() % (15 - 0 + 1) + 0);

        auto random_scale = (float) (rand() % (80 - 15 + 1) + 15) / 100;

        auto obj = new DrawableObject(*models["tree"], *shaders["lambert"], *materials["tree"]);
        obj->add_translation(glm::vec3{random_x, 0, random_z});
        obj->add_scale(glm::vec3{random_scale});
        drawable_objects.push_back(obj);
    }

    for (int i = 0; i < 50; ++i) {
        auto random_x = (rand() % (24 - 0 + 1) + 0) - 12;
        auto random_z = -(rand() % (15 - 0 + 1) + 0);
        auto obj = new DrawableObject(*models["bush"], *shaders["lambert"], *materials["bush"]);
        obj->add_translation(glm::vec3{random_x, 0, random_z});

        drawable_objects.push_back(obj);
    }

    for (int i = 0; i < 20; ++i) {
        auto random_x = (rand() % (24 - 0 + 1) + 0) - 12;
        auto random_z = -(rand() % (15 - 0 + 1) + 0);
        auto obj = new DrawableObject(*models["suzie-smooth"], *shaders["phong"], *materials["bush"]);

        auto random_scale = (float) (rand() % (30 - 10 + 1) + 10) / 100;

        obj->add_translation(glm::vec3{random_x, 0.1, random_z});
        obj->add_scale(glm::vec3{random_scale});

        drawable_objects.push_back(obj);
    }


    for (auto &drawable_object: this->drawable_objects) {
        drawable_object->apply_transform();
    }
}

void SceneForest::init_skybox() {
    auto texture =
            std::make_shared<SkyBoxTexture>("resources\\textures\\posx.jpg",
                                            "resources\\textures\\negx.jpg",
                                            "resources\\textures\\posy.jpg",
                                            "resources\\textures\\negy.jpg",
                                            "resources\\textures\\posz.jpg",
                                            "resources\\textures\\negz.jpg");

    this->skybox = std::make_shared<SkyBox>(*shaders["skybox"], texture);
}



