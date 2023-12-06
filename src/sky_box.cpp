#include "sky_box.h"

//
// Created by Martin Minarik
//

SkyBox::SkyBox(Shader &shader, const shared_ptr<SkyBoxTexture> &texture)
        : shader(shader), texture(texture) {

    //Vertex Array Object (VAO)
    VBO = 0;
    glGenBuffers(1, &VBO); // generate the VBO
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(skycube), &skycube[0], GL_STATIC_DRAW);

    VAO = 0;
    glGenVertexArrays(1, &VAO); //generate the VAO
    glBindVertexArray(VAO); //bind the VAO
    glBindBuffer(GL_ARRAY_BUFFER, VBO);

    //enable vertex attributes
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (GLvoid*)0);

}

void SkyBox::draw() {
    shader.use();
    shader.upload_texture(this->texture.get());
    shader.upload("intensity", this->intensity);

    glBindVertexArray(this->VAO);
    glDrawArrays(GL_TRIANGLES, 0, 36);

    shader.unbind();
}

SkyBox::~SkyBox() {
    glDeleteBuffers(1, &VBO);
    glDeleteVertexArrays(1, &VAO);
}

float SkyBox::get_intensity() const {
    return intensity;
}

void SkyBox::set_intensity(float intensity) {
    SkyBox::intensity = intensity;
}





