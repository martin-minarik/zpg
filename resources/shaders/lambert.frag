#version 400
#define MAX_N_LIGHTS 10
in vec3 world_position;
in vec3 world_normal;
out vec4 frag_colour;

// lights
struct Light
{
    vec3 position;
    vec3 color;

    vec3 direction;

    float k_constant;
    float k_linear;
    float k_quadratic;

    float cut_off;

    int type;
};

uniform Light lights[MAX_N_LIGHTS];
uniform int n_lights;

// material
uniform  vec4 object_color;
uniform  vec4 ambient_color;
uniform float r_a;
uniform float r_d;

float calc_attenuation (float k_constant, float k_linear, float k_quadratic, float distance){
    float result = 1.0 / (k_constant + (k_linear * distance) + (k_quadratic * pow(distance, 2)));
    return max(result, 0.0);
}

void main () {
    vec4 diffuse = vec4 (0);

    // Ambient
    vec4 ambient = ambient_color * r_a;

    for (int i=0; i < n_lights; ++i)
    {
        vec3 light_direction;
        float attenuation = 1;

        // Directional light
        if (lights[i].type == 1)
        {
            light_direction = normalize(lights[i].position - world_position);
        }

        else {
            light_direction = normalize(lights[i].position - world_position);
            // Spotlight
            if (lights[i].type == 2)
            {
                float theta = dot(light_direction, normalize(-lights[i].direction));
                if (theta <= lights[i].cut_off)
                continue;
            }
        }

        // Point light or Spotlight
        if(lights[i].type != 1)
        {
            // Attenuation
            float light_distance = length(lights[i].position - world_position);
            attenuation =
            calc_attenuation(
            lights[i].k_constant,
            lights[i].k_linear,
            lights[i].k_quadratic,
            light_distance);
        }

        // Diffuse
        float diffuse_strength = max(dot(normalize(light_direction), normalize(world_normal)), 0.0);
        diffuse += vec4 ((diffuse_strength * r_d * attenuation) * lights[i].color, 0);
    }

    // Final color
    frag_colour = (ambient + diffuse) * object_color;
}