#version 460

layout (location = 0) in vec3 VertPosition;
layout (location = 1) in vec3 VertNormal;
layout (location = 2) in vec2 VertTextureCoords;



out FragmentInput {
    vec3 Normal;
    vec2 TextureCoords;
    vec3 FragPosition;
    vec3 FragViewPos;
} FragOut;


uniform mat4 u_Transform;
uniform mat4 u_View;
uniform mat4 u_Projection;

void main()
{

    gl_Position = u_Projection * u_View * u_Transform * vec4(VertPosition, 1.0);

    FragOut.Normal = mat3(transpose(inverse(u_Transform))) * VertNormal;
    FragOut.TextureCoords = VertTextureCoords;
    FragOut.FragPosition =  vec3(u_Transform * vec4(VertPosition, 1.0));
    FragOut.FragViewPos = vec3(u_View * u_Transform * vec4(VertPosition, 1.0));
}
