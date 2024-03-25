#version 460

struct Light {
    vec3 Position;
    vec3 Color;
};

vec3 CalculateAmbientLight(vec3 ambientStrength, vec3 lightColor)
{
    return ambientStrength * lightColor;
}

vec3 CalculateDiffuseLight(vec3 normal, vec3 lightDir, vec3 lightColor)
{
    float diff = max(dot(normal, lightDir), 0.0);
    
    return diff * lightColor;
}

vec3 CalculateSpecularLight(vec3 normal, vec3 lightDir, vec3 viewDir, vec3 lightColor)
{

    vec3 reflectDir = reflect(-lightDir, normal);

    float spec = pow(max(dot(viewDir, reflectDir), 0.0), 32);

    return 1.0f * spec * lightColor;
}

