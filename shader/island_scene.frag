#version 460

#define LIGHT_NUMBER 1

in vec3 FragNormal;
in vec2 FragTextureCoords;
in vec3 FragPos;

out vec4 FragColor;

uniform sampler2D u_Texture;

uniform vec3 u_ViewPos;


uniform struct Light {
    vec3 Position;
    vec3 Color;
}[LIGHT_NUMBER] u_Lights;



vec3 CalculateAmbientLight(vec3 ambientStrength, vec3 lightColor);
vec3 CalculateDiffuseLight(vec3 normal, vec3 lightDir, vec3 lightColor);

vec3 CalculateSpecularLight(vec3 normal, vec3 lightDir, vec3 viewDir, vec3 lightColor);


void main() 
{
	vec3 norm = normalize(FragNormal);
    vec3 viewDir = normalize(u_ViewPos - FragPos);
	vec3 textureColor = texture(u_Texture, FragTextureCoords).rgb;
    vec3 ambient = CalculateAmbientLight(vec3(0.2), vec3(1.0));
    vec3 diffuse = vec3(0.0);
    vec3 specular = vec3(0.0);

    for(int i = 0; i < LIGHT_NUMBER; i++)
    {
        vec3 lightDir = normalize(u_Lights[i].Position - FragPos);

        diffuse = CalculateDiffuseLight(norm, lightDir, u_Lights[i].Color);
        specular = CalculateSpecularLight(norm, lightDir, viewDir, u_Lights[i].Color);
    }


    vec3 result = (ambient + diffuse + specular) * textureColor;
    FragColor = vec4(result, 1.0);
}
