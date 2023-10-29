//
// Created by Martin Minarik
//

#pragma once

#include "scenes/scene.h"
#include "models/model_factory.h"
#include "mouse_handler.h"


class Scene4Spheres : public Scene {
private:
    void init_shader() override;

    void init_models() override;

protected:
    void init_materials() override;

    void init_camera() override;

    void init_light() override;

    void init_drawable_objects() override;
};

