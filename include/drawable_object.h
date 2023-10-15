#pragma once

#include <vector>
#include <GL/glew.h>
#include "shader.h"
#include "transformation/transform.h"
#include "models/model.h"

class DrawableObject {
public:
    explicit DrawableObject(Model &model, Shader &shader);

    void draw();

public:
    Shader &shader;
    Model &model;

    Transformation transform;
};
