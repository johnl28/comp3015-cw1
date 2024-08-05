#version 460
layout (vertices=4) out;

in ControlInput {
    vec3 Normal;
    vec2 TextureCoords;
    vec3 FragPosition;
    vec3 FragViewPos;
} cIn[];

out EvaluationInput {
    vec2 TextureCoords;
} cOut[];

void ComputeTessellation()
{
    if (gl_InvocationID != 0) 
    {
        return;    
    }

 
    float resolution = 16;
    float tessLevels[4] = { resolution, resolution, resolution, resolution};
    gl_TessLevelOuter = tessLevels;

    gl_TessLevelInner[0] = resolution;
    gl_TessLevelInner[1] = resolution;
}

void main()
{
    cOut[gl_InvocationID].TextureCoords = cIn[gl_InvocationID].TextureCoords;
    gl_out[gl_InvocationID].gl_Position = gl_in[gl_InvocationID].gl_Position;

    ComputeTessellation();
}