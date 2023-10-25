#version 400
layout(location=0) in vec3 vertex_position;
layout(location=1) in vec3 vertex_normal;

out vec3 world_position;
out vec3 world_normal;

uniform mat4 model_matrix;
uniform mat4 view_matrix;
uniform mat4 projection_matrix;

void main () {
    world_position = vec3(model_matrix * vec4 (vertex_position, 1.0));
    world_normal = normalize(vec3(model_matrix * vec4(vertex_normal, 0.0)));

    gl_Position = projection_matrix * view_matrix * model_matrix * vec4(vertex_position, 1);
}