#version 460

layout (vertices=4) out;

in ControlIn {

    vec3 Normal;
    vec2 TextureCoords;
    vec3 FragPosition;
    vec3 FragViewPos;

} cIn[];

out ControlOut {
    vec3 Normal;
    vec2 TextureCoords;
} cOut[];


void main()
{
    // pass attributes through
    cOut[gl_InvocationID].Normal = cIn[gl_InvocationID].Normal;
    cOut[gl_InvocationID].TextureCoords = cIn[gl_InvocationID].TextureCoords;
    gl_out[gl_InvocationID].gl_Position = gl_in[gl_InvocationID].gl_Position;

    // invocation zero controls tessellation levels for the entire patch
    if (gl_InvocationID == 0) {
    
        float tessLevels[4] = {4,4,4,4};

        gl_TessLevelOuter = tessLevels;

        gl_TessLevelInner[0] = 4;
        gl_TessLevelInner[1] = 4;
    
    }
}