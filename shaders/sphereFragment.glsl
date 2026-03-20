#version 330 core
out vec4 FragColor;

uniform vec3 sphereColor;

void main()
{
    FragColor = vec4(sphereColor, 1.0);
}
