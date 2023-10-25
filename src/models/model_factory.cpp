#include "models/model_factory.h"

//
// Created by Martin Minarik
//

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
    return new Model(triangle, 18);
}

Model *ModelFactory::create_square() {
    return new Model(square, 36);
}

Model *ModelFactory::create_cube() {
    return new Model(cube, 144);
}

Model *ModelFactory::create_plain() {
    return new Model(plain, 36);
}

Model *ModelFactory::create_sphere() {
    return new Model(sphere, 2880);
}

Model *ModelFactory::create_suzie(bool smooth) {
    if (smooth)
        return new Model(suziSmooth, 2904);

    return new Model(suziFlat, 2904);
}








