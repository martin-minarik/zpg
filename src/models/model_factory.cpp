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

    } else if (name == "uv_plain") {
        return create_uv_plain();
    }

    throw std::runtime_error("Model not found!");
}

Model *ModelFactory::create_triangle() {
    return Model::from_position_normal(triangle);
}

Model *ModelFactory::create_square() {
    return Model::from_position_normal(square);
}

Model *ModelFactory::create_cube() {
    return Model::from_position_normal(cube);
}

Model *ModelFactory::create_plain() {
    return Model::from_position_normal(plain);
}

Model *ModelFactory::create_sphere() {
    return Model::from_position_normal(sphere);
}

Model *ModelFactory::create_suzie(bool smooth) {
    if (smooth)
        return Model::from_position_normal(suziSmooth);

    return Model::from_position_normal(suziFlat);
}

Model *ModelFactory::create_tree() {
    return Model::from_position_normal(tree);
}

Model *ModelFactory::create_bushes() {
    return Model::from_position_normal(bushes);
}

Model *ModelFactory::create_gift() {
    return Model::from_position_normal(gift);
}

Model *ModelFactory::create_uv_plain() {
    return Model::from_position_normal_uv(uv_plain);
}

Model *ModelFactory::create_from_file(const std::string &name) {
    return Model::from_file(name.c_str());
}
