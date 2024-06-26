#include "scenes/scene_week_9_night.h"

//
// Created by Martin Minarik
//

void SceneWeek9Night::init_shader() {
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

void SceneWeek9Night::init_materials() {
    this->materials["material1"] = new Material({0.3, 0.7, 0.3, 1});
    this->materials["material2"] = new Material({0.7, 0.3, 0.3, 1});
    this->materials["material3"] = new Material({0.3, 0.3, 0.7, 1});
    this->materials["material4"] = new Material();

    this->materials["bush_material"] = new Material(glm::vec4{0.2, 0.6, 0.2, 1});

    {
        auto material = new Material();
        auto texture = std::make_shared<Texture>(
                "resources\\textures\\grass-2500-mm-architextures.jpg");
        material->set_texture(texture);
        material->set_texture_resolution(20);
        this->materials["floor_material"] = material;
    }

    {
        auto material = new Material();
        auto texture = std::make_shared<Texture>("resources\\textures\\model.png");
        material->set_texture(texture);
        this->materials["house_material"] = material;
    }

    {
        auto material = new Material();
        auto texture = std::make_shared<Texture>("resources\\textures\\Tank_Body.BMP");
        material->set_texture(texture);
        this->materials["tiger_normal_material"] = material;
    }

    {
        auto material = new Material();
        auto texture = std::make_shared<Texture>("resources\\textures\\Tank_Body_Forest.BMP");
        material->set_texture(texture);
        this->materials["tiger_forest_material"] = material;
    }

    {
        auto material = new Material();
        auto texture = std::make_shared<Texture>("resources\\textures\\Tank_Body_Desert.BMP");
        material->set_texture(texture);
        this->materials["tiger_desert_material"] = material;
    }

    {
        auto material = new Material();
        auto texture = std::make_shared<Texture>("resources\\textures\\Tank_Body_Snow.BMP");
        material->set_texture(texture);
        this->materials["tiger_snow_material"] = material;
    }

    {
        auto material = new Material();
        auto texture = std::make_shared<Texture>("resources\\textures\\model.png");
        material->set_texture(texture);
        this->materials["house_material"] = material;
    }

}

void SceneWeek9Night::init_camera() {
    this->camera = new Camera();
    for (auto &item: shaders) {
        this->camera->attach_observer(item.second);
    }
    camera->attach_observer(dynamic_cast<Spotlight *>(lights[0]));

    camera->set_eye({0, 2, 10});

    camera->notify_observers();
    MouseHandler::get_instance().set_camera(this->camera);
    KeyBoardHandler::get_instance().set_camera(this->camera);
}

void SceneWeek9Night::init_models() {
    this->models["sphere"] = ModelFactory::create_by_name("sphere");
    this->models["plain"] = ModelFactory::create_by_name("plain");
    this->models["uv_plain"] = ModelFactory::create_by_name("uv_plain");
    this->models["house"] = ModelFactory::create_from_file("resources\\models\\model.obj");
    this->models["tiger"] = ModelFactory::create_from_file("resources\\models\\tiger_fix.obj");
    this->models["bush"] = ModelFactory::create_by_name("bushes");
}

void SceneWeek9Night::init_light() {
    {
        auto *light = new Spotlight(this->lights.size());
        this->lights.push_back(light);
    }

    {
        auto *light = new PointLight(this->lights.size());
        light->set_position(glm::vec3{12.0, 2, 0.0});
        light->set_attenuation({1, 0.5, 0});
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

void SceneWeek9Night::init_drawable_objects() {
    auto house2 = new DrawableObject(*models["house"], *shaders["lambert"], *materials["house_material"]);
    drawable_objects.push_back(house2);

    auto floor = new DrawableObject(*models["uv_plain"], *shaders["lambert"], *materials["floor_material"]);
    drawable_objects.push_back(floor);

    auto house1 = new DrawableObject(*models["house"], *shaders["lambert"], *materials["house_material"]);
    drawable_objects.push_back(house1);

    auto sphere1 = new DrawableObject(*models["sphere"], *shaders["constant"], *materials["material1"]);
    drawable_objects.push_back(sphere1);

    auto sphere2 = new DrawableObject(*models["sphere"], *shaders["lambert"], *materials["material2"]);
    drawable_objects.push_back(sphere2);

    auto sphere3 = new DrawableObject(*models["sphere"], *shaders["phong"], *materials["material3"]);
    drawable_objects.push_back(sphere3);

    auto sphere4 = new DrawableObject(*models["sphere"], *shaders["blinn"], *materials["material4"]);
    drawable_objects.push_back(sphere4);

    auto tiger_normal = new DrawableObject(
            *models["tiger"], *shaders["blinn"], *materials["tiger_normal_material"]);
    drawable_objects.push_back(tiger_normal);

    auto tiger_forest = new DrawableObject(
            *models["tiger"], *shaders["phong"], *materials["tiger_forest_material"]);
    drawable_objects.push_back(tiger_forest);

    auto tiger_desert = new DrawableObject(
            *models["tiger"], *shaders["lambert"], *materials["tiger_desert_material"]);
    drawable_objects.push_back(tiger_desert);

    auto tiger_snow = new DrawableObject(
            *models["tiger"], *shaders["lambert"], *materials["tiger_snow_material"]);
    drawable_objects.push_back(tiger_snow);

    for (int i = 0; i < 100; ++i) {
        auto random_x = (rand() % (24 - 0 + 1) + 0) - 12;
        auto random_z = (rand() % (30 - 0 + 1) + 0) - 15;
        auto obj = new DrawableObject(*models["bush"], *shaders["lambert"], *materials["bush_material"]);
        obj->add_translation(glm::vec3{random_x, 0, random_z});

        drawable_objects.push_back(obj);
    }

    sphere1->add_translation(glm::vec3(2, 1, -2), false);
    sphere2->add_translation(glm::vec3(-2, 1, -2), false);
    sphere3->add_translation(glm::vec3(6, 1, -2), false);
    sphere4->add_translation(glm::vec3(-6, 1, -2), false);

    tiger_normal->add_translation(glm::vec3(3, 0, -10), false);
    tiger_forest->add_translation(glm::vec3(-3, 0, -10), false);
    tiger_desert->add_translation(glm::vec3(9, 0, -10), false);
    tiger_snow->add_translation(glm::vec3(-9, 0, -10), false);

    floor->add_scale(glm::vec3(100, 1, 100), false);

    house1->add_translation(glm::vec3(22, 0, 0), false);
    house1->add_rotation(90, glm::vec3(0, 1, 0), false);

    house2->add_translation(glm::vec3(-22, 0, 0), false);
    house2->add_rotation(90, glm::vec3(0, 1, 0), false);

    for (auto &drawable_object: this->drawable_objects) {
        drawable_object->apply_transform();
    }
}

void SceneWeek9Night::init_skybox() {
    auto texture =
            std::make_shared<SkyBoxTexture>("resources\\textures\\posx.jpg",
                                            "resources\\textures\\negx.jpg",
                                            "resources\\textures\\posy.jpg",
                                            "resources\\textures\\negy.jpg",
                                            "resources\\textures\\posz.jpg",
                                            "resources\\textures\\negz.jpg");

    this->skybox = std::make_shared<SkyBox>(*shaders["skybox"], texture);
    this->skybox->set_intensity(0.2f);
}