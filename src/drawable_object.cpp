#include "drawable_object.h"

DrawableObject::DrawableObject(Model &model, Shader &shader) : model(model), shader(shader) {

}

void DrawableObject::draw() {
    shader.use();
    shader.upload_matrix("model_matrix", this->transform.matrix);
    model.draw();
}
