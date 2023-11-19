#pragma once

//
// Created by Martin Minarik
//

#include "scenes/scene.h"
#include "models/model_factory.h"
#include "mouse_handler.h"
#include "light/directional_light.h"



class SceneWeek9Night : public Scene {
private:
    void init_shader() override;

    void init_models() override;

private:
    void init_materials() override;

    void init_camera() override;

    void init_light() override;

    void init_drawable_objects() override;

    void init_skybox() override;
};
