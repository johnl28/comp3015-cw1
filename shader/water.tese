#version 460
layout (quads, equal_spacing, ccw) in;

const float WAVE_LENGTH = 20;
const float WAVE_SPEED = 1;
const float AMPLITUDE = 10;


uniform mat4 u_View;
uniform mat4 u_Projection;
uniform float u_Time;


in EvaluationInput {
    vec2 TextureCoords;
} eInput[];

out FragmentInput {
    vec3 Normal;
    vec2 TextureCoords;
    vec3 FragPosition;
    vec3 FragViewPos;
} eOut;


vec2 GetTextureInterpolation()
{
    vec2 t0 = eInput[0].TextureCoords + (eInput[1].TextureCoords - eInput[0].TextureCoords) * gl_TessCoord.x;
    vec2 t1 = eInput[2].TextureCoords + (eInput[3].TextureCoords - eInput[2].TextureCoords)* gl_TessCoord.x;
    return (t1 - t0) * gl_TessCoord.y + t0;
}

vec4 GetPositionInterpolation()
{
    vec4 position0 = gl_in[0].gl_Position + (gl_in[1].gl_Position - gl_in[0].gl_Position) * gl_TessCoord.x;
    vec4 position1 = gl_in[2].gl_Position + (gl_in[3].gl_Position - gl_in[2].gl_Position) * gl_TessCoord.x;

    return position0 + (position1 - position0) * gl_TessCoord.y;
}


float CalculateWaveHeight(float x)
{
    return AMPLITUDE * sin(x / WAVE_LENGTH + u_Time * WAVE_SPEED);
}

vec3 CalculateWaveNormal(float x)
{
    return vec3((AMPLITUDE / WAVE_LENGTH) * -cos(x / WAVE_LENGTH + u_Time * WAVE_SPEED), 1, 0);
}


void main()
{
    vec4 position = GetPositionInterpolation();
    position.y += CalculateWaveHeight(position.x);
    
    eOut.TextureCoords = GetTextureInterpolation();
    eOut.Normal = CalculateWaveNormal(position.x);

    eOut.FragPosition = position.xyz;
    eOut.FragViewPos = (u_View * position).xyz;

    gl_Position = u_Projection * u_View * position;
}
