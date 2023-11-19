#include "texture.h"

//
// Created by Martin Minarik
//

Texture::Texture(const std::string &filepath) {
    glActiveTexture(GL_TEXTURE0);
    this->texture_id = SOIL_load_OGL_texture(filepath.c_str(),
                                             SOIL_LOAD_RGBA,
                                             SOIL_CREATE_NEW_ID,
                                             SOIL_FLAG_INVERT_Y);

    if (!this->texture_id) {
        std::cout << "An error occurred while loading texture." << std::endl;
        exit(EXIT_FAILURE);
    }

}

Texture::~Texture() {
    glDeleteTextures(1, &this->texture_id);
}


void Texture::bind() const {
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, this->texture_id);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
}

void Texture::unbind() {
    glBindTexture(GL_TEXTURE_2D, 0);
}

