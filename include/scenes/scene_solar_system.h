//
// Created by Martin Minarik
//

#pragma once

#include "scenes/scene.h"
#include "models/model_factory.h"
#include "mouse_handler.h"
#include "transformation/rotation.h"

class SceneSolarSystem : public Scene {

public:
    void update(float delta_time) override;

private:
    void init_shader() override;

    void init_models() override;

    void init_materials() override;

    void init_camera() override;

    void init_light() override;

    void init_drawable_objects() override;

private:
    std::shared_ptr<Rotation> sun_rotation;
    std::shared_ptr<Rotation> moon_rotation;

};
