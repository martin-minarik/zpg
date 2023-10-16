#include "drawable_object.h"

DrawableObject::DrawableObject(Model &model, Shader &shader) : model(model), shader(shader) {

}

void DrawableObject::draw() {
    shader.use();
    shader.upload_transformation(reinterpret_cast<TransformationComponent *>(&this->transformation));
    model.draw();
}
