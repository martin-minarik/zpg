#pragma once

#include <GL/glew.h>

#include <exception>

class Model {
public:
    template<int N>
    explicit Model(const float (&vertices)[N], int number_of_vertices): Model(vertices, N, number_of_vertices) {

    }


    explicit Model(const float *vertices, int size, int number_of_vertices);


    void draw() const;

protected:
    void make_vbo(const float *vertices, int size);

    void make_vao();

protected:
    int number_of_vertices = 0;
    GLuint VBO = 0;
    GLuint VAO = 0;
};