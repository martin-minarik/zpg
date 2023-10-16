#include "models/model.h"

Model::Model(const float *vertices, int size, int number_of_vertices) : number_of_vertices(number_of_vertices) {
    make_vbo(vertices, size);
    make_vao();
}

void Model::draw() const {
    glBindVertexArray(this->VAO);
    glDrawArrays(GL_TRIANGLES, 0, this->number_of_vertices);
}

void Model::make_vbo(const float *vertices, int size) {
    this->VBO = 0;
    glGenBuffers(1, &this->VBO); // generate the VBO
    glBindBuffer(GL_ARRAY_BUFFER, this->VBO);
    glBufferData(GL_ARRAY_BUFFER, size * sizeof(float), vertices, GL_STATIC_DRAW);
}

void Model::make_vao() {
    this->VAO = 0;
    glGenVertexArrays(1, &this->VAO); //generate the VAO
    glBindVertexArray(this->VAO); //bind the VAO
    glBindBuffer(GL_ARRAY_BUFFER, this->VBO);

    glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(1);

    glVertexAttribPointer(
            0,
            3,
            GL_FLOAT,
            GL_FALSE,
            sizeof(float) * 6,
            (GLvoid *) nullptr);
    glVertexAttribPointer(
            1,
            3,
            GL_FLOAT,
            GL_FALSE,
            sizeof(float) * 6,
            (GLvoid *) (sizeof(float) * 3));
}



