#include "scene.h"
#include "plain.h"
#include "sphere.h"
#include "suzi_flat.h"
#include "suzi_smooth.h"

Scene::Scene() {
    init_shader();
    init_shapes();
}

Scene::~Scene() {
    for (auto &item: shaders) {
        delete item.second;
        item.second = nullptr;
    }
}

void Scene::init_shader() {
    char *vertex_shader =
            "#version 330\n"
            "layout(location=0) in vec3 vertex_position;"
            "layout(location=1) in vec3 vertex_color;"
            "out vec3 color;"
            "uniform mat4 model_matrix;"
            "void main () {"
            "     gl_Position = model_matrix * vec4(vertex_position, 1);"
            "     color  = vertex_color;"
            "}";


    char *fragment_shader_vertex =
            "#version 330\n"
            "out vec4 frag_colour;"
            "in vec3 color;"
            "void main () {"
            "     frag_colour = vec4(color, 1);"
            "}";

    char *fragment_shader_yellow =
            "#version 330\n"
            "out vec4 frag_colour;"
            "in vec3 color;"
            "void main () {"
            "     frag_colour = vec4 (1.0, 1.0, 0.0, 1.0);"
            "}";

    char *fragment_shader_green =
            "#version 330\n"
            "out vec4 frag_colour;"
            "in vec3 color;"
            "void main () {"
            "     frag_colour = vec4 (0, 1.0, 0.0, 1.0);"
            "}";

    this->shaders["vertex_color"] = new Shader(vertex_shader, fragment_shader_vertex);
    this->shaders["yellow"] = new Shader(vertex_shader, fragment_shader_yellow);
    this->shaders["green"] = new Shader(vertex_shader, fragment_shader_green);
}

void Scene::init_shapes() {
    shapes.emplace_back(SUZI_SMOOTH_VERTICES, *shaders["vertex_color"]);
//    shapes.emplace_back(Shape::SQUARE_VERTICES, *shaders["vertex_color"]);
//    shapes.emplace_back(Shape::TRIANGLE_VERTICES, *shaders["green"]);
//    shapes.emplace_back(Shape::TRIANGLE_VERTICES, *shaders["vertex_color"]);
//    shapes.emplace_back(Shape::SQUARE_VERTICES, *shaders["yellow"]);
}

void Scene::draw() {
    for (auto &shape: shapes) {
        shape.draw();
    }
}

void Scene::update(float delta) {
    shapes[0].transform.add(new Rotate(5 * delta, glm::vec3(0, 1, 0)));
    shapes[0].transform.apply();
}
