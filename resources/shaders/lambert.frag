#version 400
in vec3 world_position;
in vec3 world_normal;
out vec4 frag_colour;
uniform vec3 light_position;
uniform vec3 light_color;
uniform  vec4 object_color;
uniform float r_a;
uniform float r_d;

void main () {
    // Constants
    vec4 ambient = vec4 (0.1, 0.1, 0.1, 1.0) * r_a;

    // Direction
    vec3 light_direction = normalize(light_position - world_position);

    // Diffuse
    float diffuse_strength = max(dot(normalize(light_direction), normalize(world_normal)), 0.0);
    vec4 diffuse = vec4 ((diffuse_strength * r_d) * light_color, 1);

    // Final color
    frag_colour = (ambient + diffuse) * object_color;
}