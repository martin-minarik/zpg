#pragma once

#include <string>
#include <map>
#include <stdexcept>

#include "models/model.h"
#include "models/vertices/triangle.h"
#include "models/vertices/square.h"
#include "models/vertices/cube.h"
#include "models/vertices/plain.h"
#include "models/vertices/sphere.h"
#include "models/vertices/suzi_flat.h"
#include "models/vertices/suzi_smooth.h"

class ModelFactory {
public:
    static Model *create_by_name(const std::string& name);

    static Model *create_triangle();

    static Model *create_square();

    static Model *create_cube();

    static Model *create_plain();

    static Model *create_sphere();

    static Model *create_suzie(bool smooth);
};
