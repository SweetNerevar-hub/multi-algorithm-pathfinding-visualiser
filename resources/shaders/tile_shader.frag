#version 410

out vec4 FragColor;

in vec4 fColor;

void main()
{
	FragColor = vec4(fColor);
}