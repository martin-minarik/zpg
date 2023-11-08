# version 400
#define MAX_N_LIGHTS 10

out vec4 frag_colour;

in vec3 world_position;
in vec3 world_normal;
uniform vec3 camera_position;

// lights
struct Light
{
    vec3 position;
    vec3 color;

    float k_constant;
    float k_linear;
    float k_quadratic;

    int type;
};

uniform Light lights[MAX_N_LIGHTS];
uniform int n_lights;

// material
uniform  vec4 object_color;
uniform int specular_power;
uniform float r_a;
uniform float r_d;
uniform float r_s;

float calc_attenuation (float k_constant, float k_linear, float k_quadratic, float distance){
    float result = 1.0 / (k_constant + (k_linear * distance) + (k_quadratic * pow(distance, 2)));
    return max(result, 0.0);
}

void main ()
{
    vec4 diffuse = vec4 (0.0f);
    vec4 specular = vec4(0.0f);

    // Ambient
    vec4 ambient = vec4(0.1, 0.1, 0.1, 1.0) * r_a;

    for (int i=0; i < n_lights; ++i)
    {
        // Directions
        vec3 camera_direction = normalize(camera_position - world_position);
        vec3 light_direction = normalize(lights[i].position - world_position);
        vec3 reflection_direction = reflect(-light_direction, world_normal);

        // Attenuation
        float light_distance = length(lights[i].position - world_position);
        float attenuation =
        calc_attenuation(
        lights[i].k_constant,
        lights[i].k_linear,
        lights[i].k_quadratic,
        light_distance);

        // Diffuse
        float diffuse_strength = max(dot(normalize(light_direction), normalize(world_normal)), 0.0);
        diffuse += vec4 ((diffuse_strength * r_d * attenuation) * lights[i].color, 1);

        // Specular
        if (diffuse_strength != 0)
        {
            float spec = max(dot(camera_direction, reflection_direction), 0.0);
            spec = pow(spec, specular_power);
            specular += spec * r_s * attenuation * vec4 (lights[i].color, 1.0);
        }
    }

    // Final color
    frag_colour = (ambient + diffuse + specular) * object_color;
}