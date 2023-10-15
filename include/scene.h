#pragma once

// std
#include <vector>
#include <map>

// ZPG
#include "shader.h"
#include "drawable_object.h"
#include "models/model.h"
#include "models/model_factory.h"


class Scene
{
public:
    Scene();

    virtual ~Scene();

    void draw();

    void update(float delta);

private:
    void init();

    void init_shader();

    void init_drawable_objects();

    void init_camera();

    std::vector<Model*> models;
    std::vector<DrawableObject*> drawable_objects;
    std::map<std::string, Shader *> shaders;
};
