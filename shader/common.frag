#version 460


struct FogParams {
    float MaxDist;
    float MinDist;
    vec4 Color;
};

vec4 CalculateFog(FogParams fogParams, vec3 fragViewPos, vec4 fragColor)
{
    float dist = length(fragViewPos);

    float fog_factor = (fogParams.MaxDist - dist) /
                  (fogParams.MaxDist - fogParams.MinDist);

    fog_factor = clamp(fog_factor, 0.0, 1.0);

    return mix(fogParams.Color, fragColor, fog_factor);
}

vec3 CalculateAmbientLight(vec3 ambientStrength, vec3 lightColor)
{
    return ambientStrength * lightColor;
}

vec3 CalculateDiffusePointLight(vec3 normal, vec3 lightDir, vec3 lightColor)
{
    float diff = max(dot(normal, lightDir), 0.0);
    
    return diff * lightColor;
}

vec3 CalculateBlinnPhong(vec3 normal, vec3 lightDir, vec3 viewDir, vec3 lightColor)
{
    vec3 halfDir = normalize(lightDir + viewDir);
    
    float spec = pow(max(dot(normal, halfDir), 0.0), 32);

    return 0.1f * spec * lightColor;
}


