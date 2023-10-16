#pragma once

// std
#include <vector>
#include <map>
#include <memory>

// ZPG
#include "shader.h"
#include "camera.h"
#include "drawable_object.h"
#include "models/model.h"
#include "models/model_factory.h"
#include "mouse_handler.h"

#include "transformation/transformation_composite.h"
#include "transformation/scale.h"
#include "transformation/translation.h"
#include "transformation/rotation.h"


class Scene
{
public:
    Scene();

    virtual ~Scene();

    void draw();

    void update(float delta_time);

private:
    void init();

    void init_shader();

    void init_drawable_objects();

    void init_transformations();

    void init_camera();


    Camera *camera;
    std::vector<Model*> models;
    std::vector<DrawableObject*> drawable_objects;
    std::map<std::string, Shader *> shaders;
    std::shared_ptr<Rotation> rotation;
};
