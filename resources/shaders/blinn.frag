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
    vec4 ambient = vec4(0.1, 0.1, 0.1, 1.0);

    // Directions
    vec3 camera_direction = normalize(camera_position - world_position);
    vec3 light_direction = normalize(light_position - world_position);
    vec3 reflection_direction = reflect(-light_direction, world_normal);
    vec3 halfway_direction = normalize(camera_direction + light_direction);


    // Diffuse
    float diffuse_strength = max(dot(normalize(light_direction), normalize(world_normal)), 0.0);
    vec4 diffuse = vec4 (diffuse_strength * light_color, 1);

    // Reflections
    float spec = max(dot(world_normal, halfway_direction), 0.0);
    spec = pow(spec, 16);
    vec4 specular =  spec * vec4 (light_color, 1.0);


    // Final color
    frag_colour = (ambient + diffuse + specular) * object_color;
//    frag_colour = vec4(1.0, 1.0, 1.0, 1.0);
}