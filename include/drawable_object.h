#pragma once

//
// Created by Martin Minarik
//



#include <vector>

#include <GL/glew.h>

#include "shader.h"
#include "models/model.h"
#include "transformation/placeable.h"

class DrawableObject : public Placeable{
public:
    explicit DrawableObject(Model &model, Shader &shader);
    void draw();

private:
    Shader &shader;
    Model &model;
};
