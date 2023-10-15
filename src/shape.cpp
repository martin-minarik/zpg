#include "shape.h"

const std::vector<float> Shape::TRIANGLE_VERTICES = {
        0.f, .5f, 0.f, 1, 1, 0,
        -.5f, -.5f, 0.f, 1, 0, 0,
        .5f, -.5f, 0.f, 0, 1, 0,
};

const std::vector<float> Shape::SQUARE_VERTICES = {
        -0.5f, -0.5f, 0.0f, 1, 0, 0,
        -0.5f, 0.5f, 0.0f, 1, 0, 0,
        0.5f, -0.5f, 0.0f, 1, 0, 0,

        0.5f, 0.5f, 0.0f, 0, 0, 1,
        -0.5f, 0.5f, 0.0f, 0, 0, 1,
        0.5f, -0.5f, 0.0f, 0, 0, 1,
};

Shape::Shape(std::vector<float> vertices, Shader &shader) : shader(shader) {
    number_of_vertices = (int) vertices.size();
    make_vbo(vertices);
    make_vao();
}

void Shape::draw() {
    shader.use();
    shader.upload_matrix("model_matrix", this->transform.matrix);

    glBindVertexArray(vao);
    glDrawArrays(GL_TRIANGLES, 0, number_of_vertices / 6);
}

void Shape::make_vbo(std::vector<float> &vertices) {
    vbo = 0;
    glGenBuffers(1, &vbo); // generate the VBO
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(float), vertices.data(), GL_STATIC_DRAW);
}

void Shape::make_vao() {
    vao = 0;
    glGenVertexArrays(1, &vao); //generate the VAO
    glBindVertexArray(vao); //bind the VAO
    glBindBuffer(GL_ARRAY_BUFFER, vbo);

    glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(1);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 6, (GLvoid *) nullptr);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 6, (GLvoid *) (sizeof(float) * 3));
}


