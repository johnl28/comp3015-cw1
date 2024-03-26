#version 460

#define MAX_POINT_LIGHTS 10

in vec3 FragNormal;
in vec2 FragTextureCoords;
in vec3 FragPos;
in vec3 FragViewPos;

out vec4 FragColor;

uniform sampler2D u_TextureDiffuse;

// uniform bool u_UseTextureOpacity;
// uniform sampler2D u_TextureOpacity;

uniform vec3 u_ViewPos;
uniform int u_ActivePointLights;

uniform struct PointLight {
    vec3 Position;
    vec3 Color;
}[MAX_POINT_LIGHTS] u_PointLights;



uniform struct FogParams {
    float MaxDist;
    float MinDist;
    vec4 Color;
} u_FogParams;


vec3 CalculateAmbientLight(vec3 ambientStrength, vec3 lightColor);
vec3 CalculateDiffusePointLight(vec3 normal, vec3 lightDir, vec3 lightColor);
vec4 CalculateFog(FogParams fogParams, vec3 fragViewPos, vec4 fragColor);
vec3 CalculateBlinnPhong(vec3 normal, vec3 lightDir, vec3 viewDir, vec3 lightColor);


void main() 
{
	vec3 norm = normalize(FragNormal);
    vec3 viewDir = normalize(u_ViewPos - FragPos);

	vec3 textureColor = texture(u_TextureDiffuse, FragTextureCoords).rgb;

    // if(u_UseTextureOpacity)
    // {
    //     vec3 textureOpacity = texture(u_TextureOpacity, FragTextureCoords).rgb;
    // 
    //     if(textureOpacity == vec3(0))
    //     {
    //         discard;
    //     }
    // }



    vec3 ambient = CalculateAmbientLight(vec3(0.2), vec3(1.0));
    vec3 diffuse = vec3(0.0);
    vec3 specular = vec3(0.0);

    for(int i = 0; i < u_ActivePointLights; i++)
    {
        vec3 lightDir = normalize(u_PointLights[i].Position - FragPos);

        diffuse = CalculateDiffusePointLight(norm, lightDir, u_PointLights[i].Color);
        specular = CalculateBlinnPhong(norm, lightDir, viewDir, u_PointLights[i].Color);
    }

    vec3 result = (ambient + diffuse + specular) * textureColor;
    
    FragColor = CalculateFog(u_FogParams, FragViewPos, vec4(result, 1.0));

}
 