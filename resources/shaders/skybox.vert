#version 400

//
// Created by Martin Minarik
//

layout (location = 0) in vec3 vertex_position;

out vec3 texture_coordinate;

uniform mat4 view_matrix;
uniform mat4 projection_matrix;
void main() {
    texture_coordinate = vertex_position;

    gl_Position = projection_matrix * mat4(mat3(view_matrix)) * vec4(vertex_position, 1);
}