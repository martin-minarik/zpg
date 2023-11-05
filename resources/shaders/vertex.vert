#version 400
layout (location = 0) in vec3 vertex_position;
layout (location = 1) in vec3 vertex_normal;

out vec3 world_position;
out vec3 world_normal;

uniform mat4 model_matrix;
uniform mat4 view_matrix;
uniform mat4 projection_matrix;

void main() {
    vec4 v4_world_position = model_matrix * vec4(vertex_position, 1.0);
    world_position = v4_world_position.xyz / v4_world_position.w;
    world_normal = normalize(transpose(inverse(mat3(model_matrix))) * vertex_normal);

    gl_Position = projection_matrix * view_matrix * model_matrix * vec4(vertex_position, 1);
}