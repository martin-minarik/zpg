#include "drawable_object.h"

//
// Created by Martin Minarik
//

DrawableObject::DrawableObject(Model &model, Shader &shader, Material &material)
        : Placeable(), model(model), shader(shader), material(material) {

}

void DrawableObject::draw() {
    shader.use();
    shader.upload_transformation(this->transformation_composite.get());
    shader.upload_material(&this->material);
    model.draw();
}
