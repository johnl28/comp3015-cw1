#version 460
layout (quads, equal_spacing, ccw) in;


in EvaluationInput {
    vec3 Normal;
    vec2 TextureCoords;
} eInput[];

out EvaluationOutput {
    vec3 Normal;
    vec2 TextureCoords;
    vec3 FragPosition;
    vec3 FragViewPos;
} eOut;


// uniforms
uniform mat4 u_View;
uniform mat4 u_Projection;


void main()
{
    // retrieve control point texture coordinates
    vec2 edgeUV0 = eInput[1].TextureCoords - eInput[0].TextureCoords;
    vec2 edgeUV1 = eInput[3].TextureCoords - eInput[2].TextureCoords;
    // bilinearly interpolate texture coordinate across patch
    vec2 t0 = eInput[0].TextureCoords + edgeUV0 * gl_TessCoord.x;
    vec2 t1 = eInput[2].TextureCoords + edgeUV1 * gl_TessCoord.x;
    vec2 texCoord = (t1 - t0) * gl_TessCoord.y + t0;

    vec4 edgePos0 = gl_in[1].gl_Position - gl_in[0].gl_Position;
    vec4 edgePos1 = gl_in[3].gl_Position - gl_in[2].gl_Position;

  // retrieve control point normals
    vec3 edgeNor0 = eInput[1].Normal - eInput[0].Normal;
    vec3 edgeNor1 = eInput[3].Normal - eInput[2].Normal;
    // bilinearly interpolate normal across patch
    vec3 n0 = eInput[0].Normal + edgeNor0 * gl_TessCoord.x;
    vec3 n1 = eInput[2].Normal + edgeNor1 * gl_TessCoord.x;


    // bilinearly interpolate position across patch
    vec4 position0 = gl_in[0].gl_Position + edgePos0 * gl_TessCoord.x;
    vec4 position1 = gl_in[2].gl_Position + edgePos1 * gl_TessCoord.x;
    vec4 position = position0 + (position1 - position0) * gl_TessCoord.y;

    eOut.Normal = (n1 - n0) * gl_TessCoord.y + n0;
    eOut.FragPosition = position.xyz;
    eOut.TextureCoords = texCoord;
    eOut.FragViewPos = (u_View * position).xyz;

    // output patch point position in clip space
    gl_Position = u_Projection*u_View*position;
}