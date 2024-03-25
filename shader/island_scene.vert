#version 460

layout (location = 0) in vec3 VertexPosition;
layout (location = 1) in vec3 VertexNormal;
layout (location = 2) in vec2 VertexTextureCoords;

out vec3 FragNormal;
out vec2 FragTextureCoords;
out vec3 FragPos;


uniform mat4 u_Transform;
uniform mat4 u_View;
uniform mat4 u_Projection;

void main()
{

    gl_Position = u_Projection * u_View * u_Transform * vec4(VertexPosition, 1.0);

    FragTextureCoords = VertexTextureCoords;

    FragPos = vec3(u_Transform * vec4(VertexPosition, 1.0));
    FragNormal = mat3(transpose(inverse(u_Transform))) * VertexNormal;
}
