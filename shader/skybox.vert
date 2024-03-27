#version 460 core

layout (location = 0) in vec3 VertexPosition;

out vec3 FragCoord;

uniform mat4 u_Projection;
uniform mat4 u_View;

void main()
{
	FragCoord = VertexPosition;
	vec4 pos = u_Projection * u_View * vec4(VertexPosition, 1.0);
	gl_Position = pos.xyww;
}

