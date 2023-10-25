# version 400
in vec3 world_position;
in vec3 world_normal;

out vec4 frag_colour;

uniform vec3 camera_position;
uniform vec3 light_position;
uniform vec3 light_color;

void main ()
{
    // Constants
    vec4 object_color = vec4 (0.385, 0.647, 0.812, 1.0);
    vec4 ambient_color = vec4(0.1, 0.1, 0.1, 1.0);
    float specularStrength = 50;

    // Directions
    vec3 cameraDirection = normalize(camera_position - world_position);
    vec3 light_direction = normalize(light_position - world_position);
    vec3 reflection_direction = reflect(-light_direction, world_normal);

    // Reflections

    float spec = pow(max(dot(cameraDirection, reflection_direction), 0.0), 32);
    vec4 specular_color = specularStrength * spec * vec4 (light_color, 1.0);

    // Diffuse
    float diff = max(dot(light_direction, world_normal), 0.0);
    vec4 diffuse_color = diff * vec4 (light_color, 1.0);

    // Final color
    frag_colour = (ambient_color + diffuse_color + specular_color) * object_color;
//    frag_colour = vec4(1.0, 1.0, 1.0, 1.0);
}