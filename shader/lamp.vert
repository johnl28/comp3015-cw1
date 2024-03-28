#version 460 core

layout (location = 0) in vec3 VertexPosition;

uniform mat4 u_Projection;
uniform mat4 u_View;
uniform mat4 u_Transform;

out FragmentInput {
    vec3 FragViewPos;
} FragOut;

void main()
{
	gl_Position = u_Projection * u_View * u_Transform * vec4(VertexPosition, 1.0);

	FragOut.FragViewPos = vec3(u_View * u_Transform * vec4(VertexPosition, 1.0));
}

