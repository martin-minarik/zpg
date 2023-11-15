#pragma once

#include <texture.h>

class SkyBoxTexture : public Texture {
public:
    explicit SkyBoxTexture(const std::string &left_face_filepath,
                           const std::string &right_face_filepath,
                           const std::string &top_face_filepath,
                           const std::string &bottom_face_filepath,
                           const std::string &front_face_filepath,
                           const std::string &back_face_filepath);

    void bind() const override;
};
