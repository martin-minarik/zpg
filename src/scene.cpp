#include "scene.h"

Scene::Scene() {
    init();
}

Scene::~Scene() {
    for (auto &item: shaders) {
        delete item.second;
        item.second = nullptr;
    }

    for (auto &model: models) {
        delete model;
    }

    for (auto &drawable_object: drawable_objects) {
        delete drawable_object;
    }
}

void Scene::init() {
    this->init_shader();
    this->init_drawable_objects();
    this->init_camera();

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
            //            "     gl_Position = vec4(vertex_position, 1);"
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

void Scene::init_drawable_objects() {
    Model *suzie_model = ModelFactory::create_by_name("suzie-flat");
    this->models.push_back(suzie_model);

    drawable_objects.push_back(new DrawableObject(*suzie_model, *shaders["vertex_color"]));
}

void Scene::init_camera() {

}

void Scene::draw() {
    for (auto &drawable_object: drawable_objects) {
        drawable_object->draw();
    }
}

void Scene::update(float delta) {
    drawable_objects[0]->transform.add(new Rotate(5 * delta, glm::vec3(0, 1, 0)));
    drawable_objects[0]->transform.apply();
}





