#version 400

//
// Created by Martin Minarik
//

in vec3 texture_coordinate;

out vec4 frag_colour;

uniform samplerCube texture_unit;
uniform float intensity;

void main () {
    frag_colour = texture(texture_unit, texture_coordinate) * intensity;
}