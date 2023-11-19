#include "models/model.h"

//
// Created by Martin Minarik
//

Model::Model(const float *vertices, int size, int number_of_vertices, bool has_uv)
        : number_of_vertices(number_of_vertices), has_uv_(has_uv) {
    make_vbo(vertices, size);
    make_vao();
}

Model::~Model() {
    glDeleteBuffers(1, &VBO);
    glDeleteVertexArrays(1, &VAO);
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

void Model::make_vbo(const std::vector<float> &vertices) {
    this->VBO = 0;
    glGenBuffers(1, &VBO); // generate the VBO
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(float), vertices.data(), GL_STATIC_DRAW);
}

void Model::bind_vbo_to_vao() {
    this->VAO = 0;
    glGenVertexArrays(1, &this->VAO); //generate the VAO
    glBindVertexArray(this->VAO); //bind the VAO
    glBindBuffer(GL_ARRAY_BUFFER, this->VBO);
}

void Model::make_vao() {
    this->bind_vbo_to_vao();

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
    if (this->has_uv_) {
        glVertexAttribPointer(
                2,
                2,
                GL_FLOAT,
                GL_FALSE,
                sizeof(float) * vertex_size,
                (GLvoid *) (sizeof(float) * (vertex_size - 2)));
    }
}

Model *Model::from_file(const char *file_path) {
    Model *model = new Model();

    auto vertices = Model::load_model(file_path, model->number_of_vertices);
    model->make_vbo(vertices);

    model->bind_vbo_to_vao();

    glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(1);
    glEnableVertexAttribArray(2);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (GLvoid *) 0);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (GLvoid *) (sizeof(float) * 3));
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (GLvoid *) (sizeof(float) * 6));

    return model;
}

std::vector<float> Model::load_model(const char *file_path, int &out_number_of_vertices) {
    std::vector<float> data;
    out_number_of_vertices = 0;

    Assimp::Importer importer;
    auto importOptions = aiProcess_Triangulate
                         | aiProcess_OptimizeMeshes
                         | aiProcess_JoinIdenticalVertices
                         | aiProcess_CalcTangentSpace;

    const aiScene *scene = importer.ReadFile(file_path, importOptions);

    if (!scene) {
        std::cout << "An error occurred while loading model." << std::endl;
        exit(EXIT_FAILURE);
    }

    aiMesh *mesh = scene->mMeshes[0];
    out_number_of_vertices = mesh->mNumFaces * 3;

    for (int i = 0; i < mesh->mNumFaces; ++i) {
        aiFace face = mesh->mFaces[i];

        for (int j = 0; j < face.mNumIndices; ++j) {
            int id = face.mIndices[j];

            //Vertex position
            aiVector3D vertex_position = mesh->mVertices[id];
            data.push_back(vertex_position.x);
            data.push_back(vertex_position.y);
            data.push_back(vertex_position.z);

            //Vertex normal
            aiVector3D vertex_normal = mesh->mNormals[id];
            data.push_back(vertex_normal.x);
            data.push_back(vertex_normal.y);
            data.push_back(vertex_normal.z);

            //Vertex uv
            aiVector3D vertex_uv = mesh->mTextureCoords[0][id];
            data.push_back(vertex_uv.x);
            data.push_back(vertex_uv.y);
        }
    }

    return data;
}


