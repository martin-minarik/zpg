#pragma once

//
// Created by Martin Minarik
//


#include <vector>

#include <GL/glew.h>

#include "shader.h"
#include "models/model.h"
#include "transformation/placeable.h"
#include "material/material.h"

class DrawableObject : public Placeable{
public:
    explicit DrawableObject(Model &model, Shader &shader, Material &material);
    void draw();

    [[nodiscard]] int get_id() const;

    void set_id(int id);

private:
    Shader &shader;
    Model &model;
    Material &material;
    int id = 0;
};
