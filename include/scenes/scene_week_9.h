#pragma once

//
// Created by Martin Minarik
//

#include "scenes/scene.h"
#include "models/model_factory.h"
#include "mouse_handler.h"
#include "light/directional_light.h"
#include "transformation/bezier.h"


class SceneWeek9 : public Scene {
public:
    void interact_spawn_object(glm::vec3 position) override;
    void interact_remove_object(int id) override;
    void update(float delta_time) override;


private:
    void init_shader() override;

    void init_models() override;

    void init_materials() override;

    void init_camera() override;

    void init_light() override;

    void init_drawable_objects() override;

    void init_skybox() override;

    int last_index = 0;

    std::shared_ptr<Bezier> bezier;
    std::vector<DrawableObject*> moving_objects;
};
