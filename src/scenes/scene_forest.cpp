#include "scenes/scene_forest.h"


void SceneForest::init_shader() {
    this->shaders["constant"] = new Shader((char *) "resources\\shaders\\vertex.vert",
                                           (char *) "resources\\shaders\\constant.frag");
    this->shaders["lambert"] = new Shader((char *) "resources\\shaders\\vertex.vert",
                                          (char *) "resources\\shaders\\lambert.frag");
    this->shaders["phong"] = new Shader((char *) "resources\\shaders\\vertex.vert",
                                        (char *) "resources\\shaders\\phong.frag");
}

void SceneForest::init_materials() {
    this->materials["plain"] = new Material(glm::vec4{0.2, 0.75, 0.2, 1});
    this->materials["tree"] = new Material(glm::vec4{0.6, 0.2, 0.9, 1});
    this->materials["bush"] = new Material(glm::vec4{0.9, 0.2, 0.7, 1});
    this->materials["sphere"] = new Material(glm::vec4{0.1, 0.7, 0.9, 1});
    this->materials["suzie"] = new Material(glm::vec4{0.9, 0.2, 0.2, 1});
    this->materials["gift"] = new Material(glm::vec4{0.9, 0.9, 0.0, 1});

}

void SceneForest::init_camera() {
    this->camera = new Camera();

    for (auto &item: shaders) {
        this->camera->attach_observer(item.second);
    }

    camera->notify_observers();
    MouseHandler::get_instance().set_camera(this->camera);
    KeyBoardHandler::get_instance().set_camera(this->camera);
}

void SceneForest::init_models() {
    this->models["plain"] = ModelFactory::create_by_name("plain");
    this->models["tree"] = ModelFactory::create_by_name("tree");
    this->models["bush"] = ModelFactory::create_by_name("bushes");
    this->models["sphere"] = ModelFactory::create_by_name("sphere");
    this->models["suzie"] = ModelFactory::create_by_name("suzie-flat");
    this->models["gift"] = ModelFactory::create_by_name("gift");
}

void SceneForest::init_light() {
    this->point_light = new PointLight(0);

    for (auto &item: shaders) {
        this->point_light->attach_observer(item.second);
    }

    this->point_light->set_position(glm::vec3{0.0, 2.0, 3});
}

void SceneForest::init_drawable_objects() {
    auto plain_ = new DrawableObject(*models["plain"], *shaders["constant"], *materials["plain"]);
    plain_->add_scale(glm::vec3(100, 1, 100), false);
    drawable_objects.push_back(plain_);

    auto suzie = new DrawableObject(*models["suzie"], *shaders["lambert"], *materials["suzie"]);
    suzie->add_translation(glm::vec3(0, 1, 2), false);
    suzie->add_scale(glm::vec3(0.5), false);
    drawable_objects.push_back(suzie);

    auto gift_ = new DrawableObject(*models["gift"], *shaders["lambert"], *materials["gift"]);
    gift_->add_translation(glm::vec3(3, 1, 2), false);
    gift_->add_scale(glm::vec3(3), false);
    drawable_objects.push_back(gift_);

    auto sphere_ = new DrawableObject(*models["sphere"], *shaders["lambert"], *materials["sphere"]);
    sphere_->add_translation(glm::vec3(-3, 1, 2), false);
    sphere_->add_scale(glm::vec3(0.5), false);
    drawable_objects.push_back(sphere_);

    for (int i = 0; i < 50; ++i) {
        auto random_x = (rand() % (30 - 0 + 1) + 0) - 15;
        auto random_z = -(rand() % (30 - 0 + 1) + 0);

        auto random_scale = (float) (rand() % (100 - 25 + 1) + 25) / 100;

        auto obj = new DrawableObject(*models["tree"], *shaders["constant"], *materials["tree"]);
        obj->add_translation(glm::vec3{random_x, 0, random_z});
        obj->add_scale(glm::vec3{random_scale});
        drawable_objects.push_back(obj);
    }

    for (int i = 0; i < 50; ++i) {
        auto random_x = (rand() % (30 - 0 + 1) + 0) - 15;
        auto random_z = -(rand() % (15 - 0 + 1) + 0);

//        auto random_scale = (float) (rand() % (100 - 25 + 1) + 25) / 100;

        auto obj = new DrawableObject(*models["bush"], *shaders["constant"], *materials["bush"]);
        obj->add_translation(glm::vec3{random_x, 0, random_z});
//        obj->add_scale(glm::vec3{random_scale});
        drawable_objects.push_back(obj);
    }


    for (auto &drawable_object: this->drawable_objects) {
        drawable_object->apply_transform();
    }
}



