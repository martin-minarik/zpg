#include "models/model_factory.h"

Model *ModelFactory::create_by_name(const std::string &name) {
    if (name == "triangle") {
        return create_triangle();

    } else if (name == "square") {
        return create_square();

    } else if (name == "cube") {
        return create_cube();

    } else if (name == "plain") {
        return create_plain();

    } else if (name == "sphere") {
        return create_sphere();

    } else if (name == "suzie-flat") {
        return create_suzie(false);

    } else if (name == "suzie-smooth") {
        return create_suzie(true);
    }

    throw std::runtime_error("Model not found!");
}

Model *ModelFactory::create_triangle() {
    return new Model(triangle, sizeof(triangle) / sizeof(float), 18);
}

Model *ModelFactory::create_square() {
    return new Model(square, sizeof(square) / sizeof(float), 36);
}

Model *ModelFactory::create_cube() {
    return new Model(cube, sizeof(cube) / sizeof(float), 144);
}

Model *ModelFactory::create_plain() {
    return new Model(plain, sizeof(plain) / sizeof(float), 36);
}

Model *ModelFactory::create_sphere() {
    return new Model(sphere, sizeof(sphere) / sizeof(float), 2880);
}

Model *ModelFactory::create_suzie(bool smooth) {
    if (smooth)
        return new Model(suziSmooth, sizeof(suziSmooth) / sizeof(float), 2904);

    return new Model(suziFlat, sizeof(suziFlat) / sizeof(float), 2904);
}








