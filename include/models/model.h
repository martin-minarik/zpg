#pragma once

//
// Created by Martin Minarik
//



#include <GL/glew.h>

#include<assimp/Importer.hpp>
#include<assimp/scene.h>
#include<assimp/postprocess.h>

#include <iostream>
#include <exception>
#include <vector>

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

    ~Model();

    void draw() const;

    static Model* from_file(const char *file_path);



private:
    Model() = default;

    void make_vbo(const float *vertices, int size);
    void make_vbo(const std::vector<float> &vertices);
    void bind_vbo_to_vao();


    void make_vao();

    static std::vector<float> load_model(const char *file_path, int &out_number_of_vertices);

private:
    bool has_uv_ = false;
    int number_of_vertices = 0;
    GLuint VBO = 0;
    GLuint VAO = 0;
};