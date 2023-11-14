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

    } else if (name == "tree") {
        return create_tree();

    } else if (name == "bushes") {
        return create_bushes();

    } else if (name == "gift") {
        return create_gift();
    }

    else if (name == "uv_plain") {
        return create_uv_plain();
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
    return new Model(plain, 6);
}

Model *ModelFactory::create_sphere() {
    return new Model(sphere, 2880);
}

Model *ModelFactory::create_suzie(bool smooth) {
    if (smooth)
        return new Model(suziSmooth, 2904);

    return new Model(suziFlat, 2904);
}

Model *ModelFactory::create_tree() {
    return new Model(tree, 92814);
}

Model *ModelFactory::create_bushes() {
    return new Model(bushes, 8730);
}

Model *ModelFactory::create_gift() {
    return new Model(gift, 66624);
}

Model *ModelFactory::create_uv_plain()
{
    return new Model(uv_plain, 6, true);
}






