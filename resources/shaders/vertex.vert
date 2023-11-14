#version 400

//
// Created by Martin Minarik
//

layout (location = 0) in vec3 vertex_position;
layout (location = 1) in vec3 vertex_normal;
layout (location = 2) in vec2 uv;

out vec3 world_position;
out vec3 world_normal;
out vec2 uvc;

uniform mat4 model_matrix;
uniform mat4 view_matrix;
uniform mat4 projection_matrix;

void main() {
    vec4 v4_world_position = model_matrix * vec4(vertex_position, 1.0);
    world_position = v4_world_position.xyz / v4_world_position.w;
    world_normal = normalize(transpose(inverse(mat3(model_matrix))) * vertex_normal);

    uvc = uv;

    gl_Position = projection_matrix * view_matrix * model_matrix * vec4(vertex_position, 1);
}