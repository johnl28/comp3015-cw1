#version 460 core

out vec4 FragColor;

uniform vec3 u_LightColor;

in FragmentInput {

    vec3 FragViewPos;

} FragIn;


uniform struct FogParams {
    float MaxDist;
    float MinDist;
    vec4 Color;
} u_FogParams;


vec4 CalculateFog(FogParams fogParams, vec3 fragViewPos, vec4 fragColor);


void main()
{
	FragColor = CalculateFog(u_FogParams, FragIn.FragViewPos, vec4(u_LightColor, 1.0));
}


