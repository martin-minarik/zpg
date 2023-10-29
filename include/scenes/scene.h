#pragma once

//
// Created by Martin Minarik
//

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


class Scene {
public:
    Scene();

    virtual ~Scene();

    virtual void init();

    virtual void draw();

    virtual void update(float delta_time);

protected:
    virtual void init_shader() = 0;

    virtual void init_models() = 0;

    virtual void init_camera() = 0;

    virtual void init_light() = 0;

    virtual void init_drawable_objects() = 0;

    Camera *camera;
    PointLight *point_light;
    std::map<std::string, Model *> models;
    std::vector<DrawableObject *> drawable_objects;
    std::map<std::string, Shader *> shaders;
};
