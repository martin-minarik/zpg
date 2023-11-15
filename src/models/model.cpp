#include "models/model.h"

//
// Created by Martin Minarik
//

Model::Model(const float *vertices, int size, int number_of_vertices, bool has_uv)
        : number_of_vertices(number_of_vertices), has_uv_(has_uv)
{
    make_vbo(vertices, size);
    make_vao();
}

Model::~Model() {
    glDeleteBuffers(1, &VBO);
    glDeleteVertexArrays(1, &VAO);
}

void Model::draw() const
{
    glBindVertexArray(this->VAO);
    glDrawArrays(GL_TRIANGLES, 0, this->number_of_vertices);
}

void Model::make_vbo(const float *vertices, int size)
{
    this->VBO = 0;
    glGenBuffers(1, &this->VBO); // generate the VBO
    glBindBuffer(GL_ARRAY_BUFFER, this->VBO);
    glBufferData(GL_ARRAY_BUFFER, size * sizeof(float), vertices, GL_STATIC_DRAW);
}

void Model::make_vao()
{
    this->VAO = 0;
    glGenVertexArrays(1, &this->VAO); //generate the VAO
    glBindVertexArray(this->VAO); //bind the VAO
    glBindBuffer(GL_ARRAY_BUFFER, this->VBO);

    glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(1);

    if (this->has_uv_)
        glEnableVertexAttribArray(2);

    auto vertex_size = (this->has_uv_) ? 8 : 6;

    glVertexAttribPointer(
            0,
            3,
            GL_FLOAT,
            GL_FALSE,
            sizeof(float) * vertex_size,
            (GLvoid *) nullptr);
    glVertexAttribPointer(
            1,
            3,
            GL_FLOAT,
            GL_FALSE,
            sizeof(float) * vertex_size,
            (GLvoid *) (sizeof(float) * 3));
    if (this->has_uv_)
    {
        glVertexAttribPointer(
                2,
                2,
                GL_FLOAT,
                GL_FALSE,
                sizeof(float) * vertex_size,
                (GLvoid *) (sizeof(float) * (vertex_size - 2)));
    }
}

bool Model::has_uv() const
{
    return has_uv_;
}



