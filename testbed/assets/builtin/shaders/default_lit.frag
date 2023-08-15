#version 410 core

#define POINT_LIGHT_COUNT 4

out vec4 f_Color;

in vec4 v_Color;
in vec3 v_Normal;
in vec3 v_WorldPosition;
in vec2 v_TexCoord;

uniform vec3 u_CameraPosition;

uniform struct DirLight {
    vec3 Direction;
    vec3 Ambient;
    vec3 Diffuse;
    vec3 Specular;
} u_DirLight;

uniform struct PointLight {
    vec3 Position;
    float Constant;
    float Linear;
    float Quadratic;
    vec3 Ambient;
    vec3 Diffuse;
    vec3 Specular;
} u_PointLights[POINT_LIGHT_COUNT];

uniform struct Material {
    sampler2D DiffuseMap;
    sampler2D SpecularMap;
    sampler2D NormalMap;
} u_Material;

vec3 DirectionalLighting(DirLight light, vec3 normal, vec3 viewDir) {
    vec3 lightDir = normalize(-light.Direction);
    float diff = max(dot(normal, lightDir), 0.0);
    vec3 reflectDir = reflect(-lightDir, normal);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), 32);

    vec3 ambient = light.Ambient * vec3(texture(u_Material.DiffuseMap, v_TexCoord));
    vec3 diffuse = light.Diffuse * diff * vec3(texture(u_Material.DiffuseMap, v_TexCoord));
    vec3 specular = light.Specular * spec * vec3(texture(u_Material.SpecularMap, v_TexCoord));

    return ambient + diffuse + specular;
}

vec3 PointLighting(PointLight light, vec3 normal, vec3 fragPos, vec3 viewDir) {
    vec3 lightDir = normalize(light.Position - fragPos);
    float diff = max(dot(normal, lightDir), 0.0);
    vec3 reflectDir = reflect(-lightDir, normal);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), 32);
    float dist = length(light.Position - fragPos);
    float attenuation = 1.0 / (light.Constant + light.Linear * dist + 
  			     light.Quadratic * (dist * dist));

    vec3 ambient = light.Ambient * vec3(texture(u_Material.DiffuseMap, v_TexCoord));
    vec3 diffuse = light.Diffuse * diff * vec3(texture(u_Material.DiffuseMap, v_TexCoord));
    vec3 specular = light.Specular * spec * vec3(texture(u_Material.SpecularMap, v_TexCoord));

    ambient  *= attenuation;
    diffuse  *= attenuation;
    specular *= attenuation;

    return ambient + diffuse + specular;
}

void main() {
    vec3 result = vec3(0.0);
    vec3 normal = normalize(v_Normal);
    vec3 viewDir = normalize(u_CameraPosition - v_WorldPosition);

    // result += DirectionalLighting(u_DirLight, normal, viewDir);
    for (int i = 0; i < POINT_LIGHT_COUNT; i++) {
        result += PointLighting(u_PointLights[i], normal, v_WorldPosition, viewDir); 
    }

    f_Color = vec4(result, 1.0);
}