#pragma once

//
// Created by Martin Minarik
//



#include <GL/glew.h>

#include <exception>

class Model
{
public:
    template<int N>
    Model(const float (&vertices)[N], int number_of_vertices)
            : Model(vertices, N, number_of_vertices, false)
    {

    }

    template<int N>
    Model(const float (&vertices)[N], int number_of_vertices, bool has_uv)
            : Model(vertices, N, number_of_vertices, has_uv)
    {

    }

    explicit Model(const float *vertices, int size, int number_of_vertices, bool has_uv);


    void draw() const;

    [[nodiscard]] bool has_uv() const;

protected:
    void make_vbo(const float *vertices, int size);

    void make_vao();

protected:
    bool has_uv_ = false;
    int number_of_vertices = 0;
    GLuint VBO = 0;
    GLuint VAO = 0;
};