#version 410

layout(location = 0) in vec2 vPos;
layout(location = 1) in vec4 vColor;

out vec4 fColor;

uniform mat4 projection;
uniform mat4 view;

void main()
{
	gl_Position = projection * view * vec4(vPos.x, vPos.y, 0.f, 1.f);
	fColor = vColor;
}