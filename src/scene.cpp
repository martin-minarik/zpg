#include "scene.h"

Scene::Scene() {
    init();
}

Scene::~Scene() {
    delete camera;

    for (auto &drawable_object: drawable_objects) {
        delete drawable_object;
    }

    for (auto &model: models) {
        delete model;
    }

    for (auto &item: shaders) {
        delete item.second;
        item.second = nullptr;
    }
}

void Scene::init() {
    this->init_shader();
    this->init_drawable_objects();
    this->init_camera();
    this->init_transformations();
}

void Scene::init_shader() {
    char *vertex_shader =
            "#version 330\n"
            "layout(location=0) in vec3 vertex_position;"
            "layout(location=1) in vec3 vertex_color;"
            "out vec3 color;"
            "uniform mat4 model_matrix;"
            "uniform mat4 view_matrix;"
            "uniform mat4 projection_matrix;"
            "void main () {"
            //            "     gl_Position = model_matrix * vec4(vertex_position, 1);"
            "     gl_Position = projection_matrix * view_matrix * model_matrix * vec4(vertex_position, 1);"
            "     color  = vertex_color;"
            "}";


    char *fragment_shader_vertex =
            "#version 330\n"
            "out vec4 frag_colour;"
            "in vec3 color;"
            "void main () {"
            "     frag_colour = vec4(color, 1);"
            "}";

    char *fragment_shader_green =
            "#version 330\n"
            "out vec4 frag_colour;"
            "in vec3 color;"
            "void main () {"
            "     frag_colour = vec4 (0, 1.0, 0.0, 1.0);"
            "}";

    this->shaders["vertex_color"] = new Shader(vertex_shader, fragment_shader_vertex);
    this->shaders["green"] = new Shader(vertex_shader, fragment_shader_green);


}

void Scene::init_drawable_objects() {
    Model *cube = ModelFactory::create_by_name("cube");
    Model *sphere_model = ModelFactory::create_by_name("sphere");
    Model *suzie_flat = ModelFactory::create_by_name("suzie-flat");
    Model *suzie_smooth = ModelFactory::create_by_name("suzie-smooth");
    this->models.push_back(sphere_model);
    this->models.push_back(suzie_flat);
    this->models.push_back(suzie_smooth);

    drawable_objects.push_back(new DrawableObject(*suzie_flat, *shaders["vertex_color"]));
    drawable_objects.push_back(new DrawableObject(*cube, *shaders["vertex_color"]));
    drawable_objects.push_back(new DrawableObject(*suzie_flat, *shaders["vertex_color"]));
    drawable_objects.push_back(new DrawableObject(*sphere_model, *shaders["vertex_color"]));
    drawable_objects.push_back(new DrawableObject(*sphere_model, *shaders["vertex_color"]));
    drawable_objects.push_back(new DrawableObject(*suzie_smooth, *shaders["vertex_color"]));
    drawable_objects.push_back(new DrawableObject(*suzie_flat, *shaders["vertex_color"]));
}

void Scene::init_transformations() {
    this->rotation.reset(new Rotation(0, glm::vec3(0, 1, 0)));


    drawable_objects[0]->transformation.add(rotation);
    drawable_objects[0]->transformation.add(
            std::make_shared<Rotation>(180, glm::vec3(0, 0, 1)));
    drawable_objects[0]->transformation.add(
            std::make_shared<Scale>(glm::vec3(0.3, 0.3, 0.3)));


    drawable_objects[1]->transformation.add(
            std::make_shared<Translation>(glm::vec3(0, 0, -5)));
    drawable_objects[1]->transformation.add(
            std::make_shared<Rotation>(180, glm::vec3(0, 0, 1)));
    drawable_objects[1]->transformation.add(rotation);


    drawable_objects[2]->transformation.add(
            std::make_shared<Translation>(glm::vec3(2, 2, -2)));


    drawable_objects[3]->transformation.add(
            std::make_shared<Translation>(glm::vec3(-2, 2, -2)));
    drawable_objects[3]->transformation.add(
            std::make_shared<Scale>(glm::vec3(0.3)));


    drawable_objects[4]->transformation.add(
            std::make_shared<Translation>(glm::vec3(2, -2, -2)));


    drawable_objects[5]->transformation.add(
            std::make_shared<Translation>(glm::vec3(-2, -2, -2)));


    drawable_objects[6]->transformation.add(
            std::make_shared<Translation>(glm::vec3(0, 0, -2)));
    drawable_objects[6]->transformation.add(
            std::make_shared<Scale>(glm::vec3(0.3, 0.3, 0.3)));

    for (auto &drawable_object: this->drawable_objects) {
        drawable_object->transformation.apply();
    }
}

void Scene::init_camera() {
    this->camera = new Camera();

    for (auto &item: shaders) {
        this->camera->attach_shader(item.second);
    }
    camera->notify_shader();
    MouseHandler::get_instance().set_camera(this->camera);
    KeyBoardHandler::get_instance().set_camera(this->camera);
}

void Scene::draw() {
    for (auto &drawable_object: drawable_objects) {
        drawable_object->draw();
    }
}

void Scene::update(float delta_time) {
    rotation->set_angle(rotation->get_angle() + 50 * delta_time);
    for (auto &drawable_object: this->drawable_objects) {
        drawable_object->transformation.apply();
    }
}






