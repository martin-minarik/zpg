#pragma once

#include <vector>

#include <GL/glew.h>

#include "shader.h"
#include "transformation/transformation_composite.h"
#include "transformation/transformation_component.h"
#include "models/model.h"
#include "models/model.h"

class DrawableObject {
public:
    explicit DrawableObject(Model &model, Shader &shader);

    void draw();


public:
    TransformationComposite transformation;

private:
    Shader &shader;
    Model &model;
};
