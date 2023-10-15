#pragma once

#include <vector>
#include <GL/glew.h>
#include "shader.h"
#include "transform.h"

class Shape {
public:
    explicit Shape(std::vector<float> vertices, Shader &shader);

    void draw();

    static const std::vector<float> SQUARE_VERTICES;
    static const std::vector<float> TRIANGLE_VERTICES;

public:
    Transformation transform;

private:
    void make_vbo(std::vector<float> &vertices);

    void make_vao();


private:
    int number_of_vertices = 0;
    Shader &shader;
    GLuint vbo = 0;
    GLuint vao = 0;
};
