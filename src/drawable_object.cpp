#include "drawable_object.h"

DrawableObject::DrawableObject(Model &model, Shader &shader) : Placeable(), model(model), shader(shader) {

}

void DrawableObject::draw() {
    shader.use();
    shader.upload_transformation(this->transformation_composite.get());
    model.draw();
}
