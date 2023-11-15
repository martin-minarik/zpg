//
// Created by Martin on 15.11.2023.
//

#include "sky_box_texture.h"
#include "texture.h"


SkyBoxTexture::SkyBoxTexture(const std::string &left_face_filepath, const std::string &right_face_filepath,
                             const std::string &top_face_filepath, const std::string &bottom_face_filepath,
                             const std::string &front_face_filepath, const std::string &back_face_filepath) {
    glActiveTexture(GL_TEXTURE0);
    this->texture_id = SOIL_load_OGL_cubemap(
            left_face_filepath.c_str(), right_face_filepath.c_str(),
            top_face_filepath.c_str(), bottom_face_filepath.c_str(),
            front_face_filepath.c_str(), back_face_filepath.c_str(),
            SOIL_LOAD_RGB,
            SOIL_CREATE_NEW_ID,
            SOIL_FLAG_MIPMAPS);

    if (!this->texture_id) {
        std::cout << "An error occurred while loading CubeMap." << std::endl;
        exit(EXIT_FAILURE);
    }
    this->bind();
}

void SkyBoxTexture::bind() const {
    glBindTexture(GL_TEXTURE_CUBE_MAP, this->texture_id);
    glEnable(GL_TEXTURE_CUBE_MAP_SEAMLESS);

}
