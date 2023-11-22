#pragma once

//
// Created by Martin Minarik
//

// Include Glew
#include "GL/glew.h"
// Include GLFW
#include "GLFW/glfw3.h"

// std
#include <vector>
#include <map>
#include <memory>
#include <string>

// ZPG
#include "shader.h"
#include "camera.h"
#include "light/light.h"
#include "drawable_object.h"
#include "models/model.h"
#include "sky_box.h"


class Scene {
public:
    Scene();

    virtual ~Scene();

    virtual void init();

    virtual void draw();

    virtual void draw_skybox();

    virtual void update(float delta_time);

protected:
    virtual void init_shader() = 0;

    virtual void init_models() = 0;

    virtual void init_materials() = 0;

    virtual void init_camera() = 0;

    virtual void init_light() = 0;

    virtual void init_drawable_objects() = 0;

    virtual void init_skybox() = 0;

    Camera *camera;
    std::map<std::string, Model *> models;
    std::map<std::string, Material *> materials;
    std::vector<Light *> lights;
    std::vector<DrawableObject *> drawable_objects;
    std::map<std::string, Shader *> shaders;

    std::shared_ptr<SkyBox> skybox;
};
