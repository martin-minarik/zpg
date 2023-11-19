#pragma once

//
// Created by Martin Minarik
//

#include <GL/glew.h>

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>
#include <assimp/cimport.h>

#include <iostream>
#include <exception>
#include <vector>

class Model {
public:
    ~Model();

    void draw() const;

    static Model *from_file(const char *file_path);

    template<int N>
    static Model *from_position_normal(const float (&vertices)[N]) {
        return Model::from_position_normal(vertices, N);
    }

    static Model *from_position_normal(const float *vertices, int size);

    template<int N>
    static Model *from_position_normal_uv(const float (&vertices)[N]) {
        return Model::from_position_normal_uv(vertices, N);
    }

    static Model *from_position_normal_uv(const float *vertices, int size);


private:
    Model() = default;

    void make_vbo(const float *vertices, int size);

    void make_vbo(const std::vector<float> &vertices);

    void bind_vbo_to_vao();

    static std::vector<float> load_model(const char *file_path, int &out_number_of_vertices);

private:
    bool has_uv_ = false;
    int number_of_vertices = 0;
    GLuint VBO = 0;
    GLuint VAO = 0;
};
