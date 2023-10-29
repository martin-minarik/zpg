# version 400
in vec3 world_position;
in vec3 world_normal;

out vec4 frag_colour;

uniform vec3 camera_position;
uniform vec3 light_position;
uniform vec3 light_color;
uniform  vec4 object_color;
uniform int specular_power;
uniform float r_a;
uniform float r_d;
uniform float r_s;

void main ()
{
    // Constants
    vec4 ambient = vec4(0.1, 0.1, 0.1, 1.0) * r_a;

    // Directions
    vec3 camera_direction = normalize(camera_position - world_position);
    vec3 light_direction = normalize(light_position - world_position);
    vec3 reflection_direction = reflect(-light_direction, world_normal);

    // Diffuse
    float diffuse_strength = max(dot(normalize(light_direction), normalize(world_normal)), 0.0);
    vec4 diffuse = vec4 ((diffuse_strength * r_d) * light_color, 1);

    // Specular
    float spec = max(dot(camera_direction, reflection_direction), 0.0);
    spec = pow(spec, specular_power);
    vec4 specular =  spec * r_s * vec4 (light_color, 1.0);


    // Final color
    frag_colour = (ambient + diffuse + specular) * object_color;
}