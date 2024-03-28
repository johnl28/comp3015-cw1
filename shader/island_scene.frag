#version 460

#define MAX_POINT_LIGHTS 10

out vec4 FragColor;


in FragmentInput {

    vec3 Normal;
    vec2 TextureCoords;
    vec3 FragPosition;
    vec3 FragViewPos;

} FragIn;


uniform bool u_UseTextureOpacity;

uniform struct TextureSamplers {
    sampler2D Diffuse;
    sampler2D AlphaMap;
} u_Textures;




uniform vec3 u_ViewPos;
uniform int u_ActivePointLights;

uniform struct PointLight {
    vec3 Position;
    vec3 Color;
    float Intensity;
}[MAX_POINT_LIGHTS] u_PointLights;


uniform struct FogParams {
    float MaxDist;
    float MinDist;
    vec4 Color;
} u_FogParams;


vec3 CalculateAmbientLight(float ambientStrength, vec3 lightColor);
vec3 CalculateDiffusePointLight(vec3 normal, vec3 lightDir, vec3 lightColor);
vec4 CalculateFog(FogParams fogParams, vec3 fragViewPos, vec4 fragColor);
vec3 CalculateBlinnPhong(vec3 normal, vec3 lightDir, vec3 viewDir, vec3 lightColor);




void main() 
{
	vec3 norm = normalize(FragIn.Normal);

    vec3 viewDir = normalize(u_ViewPos - FragIn.FragPosition);

	vec4 textureColor = texture(u_Textures.Diffuse, FragIn.TextureCoords);

    if(u_UseTextureOpacity)
    {
        float textureOpacity = texture(u_Textures.AlphaMap, FragIn.TextureCoords).r;
    
        if(textureOpacity == 0)
        {
            discard;
        }
    }


    vec3 ambient = CalculateAmbientLight(0.01, vec3(1.0));
    vec3 diffuse = vec3(0.0);
    vec3 specular = vec3(0.0);

    for(int i = 0; i < u_ActivePointLights; i++)
    {

        vec3 fragToLight = u_PointLights[i].Position - FragIn.FragPosition;
        float distanceToLight = length(fragToLight);
        vec3 lightDir = normalize(fragToLight);

        float attenuation = 1.0 / (1.0 + 0.09 * distanceToLight + 0.032 * distanceToLight * distanceToLight);

        vec3 intensityColor = u_PointLights[i].Color *  u_PointLights[i].Intensity;

        diffuse += CalculateDiffusePointLight(norm, lightDir, intensityColor) * attenuation;
        specular += CalculateBlinnPhong(norm, lightDir, viewDir, intensityColor) * attenuation;

    }

    vec4 result = vec4(ambient + diffuse + specular, 1.0) * textureColor;
    
    FragColor = CalculateFog(u_FogParams, FragIn.FragViewPos, result);

}
 