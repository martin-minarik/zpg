#version 400
//#define MAX_N_LIGHTS 10
in vec3 world_position;
in vec3 world_normal;
out vec4 frag_colour;

// lights
uniform vec3 light_position;
uniform vec3 light_color;
uniform float light_k_constant;
uniform float light_k_linear;
uniform float light_k_quadratic;

// material
uniform  vec4 object_color;
uniform float r_a;
uniform float r_d;

float calc_attenuation (float k_constant, float k_linear, float k_quadratic, float distance){
    float result = 1.0 / (k_constant + (k_linear * distance) + (k_quadratic * pow(distance, 2)));
    return max(result, 0.0);
}

void main () {
    // Ambient
    vec4 ambient = vec4 (0.1, 0.1, 0.1, 1.0) * r_a;

    //    for (int i=0; i < n_lights; ++i)
    //    {
    //
    //    }

    // Direction
    vec3 light_direction = normalize(light_position - world_position);

    // Attenuation
    float light_distance = length(light_position - world_position);
    float attenuation = calc_attenuation(light_k_constant, light_k_linear, light_k_quadratic, light_distance);

    // Diffuse
    float diffuse_strength = max(dot(normalize(light_direction), normalize(world_normal)), 0.0);
    vec4 diffuse = vec4 ((diffuse_strength * r_d) * light_color, 1);

    // Final color
    frag_colour = (ambient + diffuse * attenuation) * object_color;
}