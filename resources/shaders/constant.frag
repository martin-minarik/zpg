#version 400

//
// Created by Martin Minarik
//

out vec4 frag_colour;

uniform  vec4 object_color;

void main () {
    frag_colour = object_color;
}