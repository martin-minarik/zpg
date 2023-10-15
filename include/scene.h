#pragma once

// std
#include <vector>
#include <map>

// ZPG
#include "shape.h"
#include "shader.h"


class Scene
{
public:
    Scene();

    virtual ~Scene();

    void draw();

    void update(float delta);

private:
    void init_shader();

    void init_shapes();

    std::vector<Shape> shapes;
    std::map<std::string, Shader *> shaders;
};
