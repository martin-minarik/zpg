#pragma once

// std
#include <vector>
#include <map>
#include <memory>
#include <string>

// ZPG
#include "shader.h"
#include "camera.h"
#include "light/point_light.h"
#include "drawable_object.h"
#include "models/model.h"
#include "models/model_factory.h"
#include "mouse_handler.h"

class Scene {
public:
    Scene();

    virtual ~Scene();

    void draw();

    void update(float delta_time);

    void scene1();
    void scene2();
    void scene3();

private:
    void init();

    void init_shader();

    void init_camera();

    void init_models();

    Camera *camera;
    PointLight *point_light;
    std::map<std::string, Model *> models;
    std::vector<DrawableObject *> drawable_objects;
    std::map<std::string, Shader *> shaders;
};
