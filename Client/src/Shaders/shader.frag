#version 330 core

out vec4 FragColor;

void main()
{
    vec3 color = vec3(0.5, 0.7, 0.3);
	FragColor = vec4(color, 1.0);
}