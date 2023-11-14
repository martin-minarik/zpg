#version 400

//
// Created by Martin Minarik
//

in vec2 uvc;

out vec4 frag_colour;

uniform sampler2D textureUnitID;
uniform bool has_texture;
uniform vec4 object_color;

void main () {
    if(has_texture)
        frag_colour = texture(textureUnitID, uvc);
    else
        frag_colour = object_color;
}