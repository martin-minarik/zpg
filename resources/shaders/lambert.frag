#version 400
in vec3 world_position;
in vec3 world_normal;
out vec4 frag_colour;
uniform vec3 light_position;
uniform vec3 light_color;

void main () {
    // Constants
    vec4 object_color = vec4 (0.385, 0.647, 0.812, 1.0);
    vec4 ambient = vec4 (0.1, 0.1, 0.1, 1.0);

    // Direction
    vec3 light_direction = normalize(light_position - world_position);

    // Diffuse
    float diff = max(dot(normalize(light_direction), normalize(world_normal)), 0.0);
    vec4 diffuse = vec4 (diff * light_color, 1);

    // Final color
    frag_colour =(ambient + diffuse) * object_color;
}