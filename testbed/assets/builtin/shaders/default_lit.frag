#version 410 core

out vec4 f_Color;

in vec4 v_Color;
in vec3 v_Normal;
in vec3 v_WorldPosition;

uniform vec3 u_LightColor;
uniform vec3 u_LightPosition;
uniform vec3 u_CameraPosition;

void main() {
    float ambientIntensity = 0.1;
    float specularIntesity = 0.6;

    vec3 normalDir = normalize(v_Normal);
    vec3 lightDir = normalize(u_LightPosition - v_WorldPosition);
    vec3 viewDir = normalize(u_CameraPosition - v_WorldPosition);
    vec3 reflectDir = reflect(-lightDir, normalDir);

    float diffuse = max(dot(normalDir, lightDir), 0.0);
    float specular = pow(max(dot(viewDir, reflectDir), 0.0), 32);

    vec3 ambientTerm = ambientIntensity * u_LightColor;
    vec3 specularTerm = specular * u_LightColor;
    vec3 diffuseTerm = diffuse * u_LightColor;

    f_Color = v_Color * vec4(ambientTerm + diffuseTerm + specularTerm, 1.0);
}