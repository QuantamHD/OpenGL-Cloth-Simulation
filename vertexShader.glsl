#version 330 core

layout (location = 0) in vec4 position;
layout (location = 1) in vec3 normals;

uniform mat4 modelViewMatrix;
uniform mat4 projectionMatrix;

out vec3 Normal;
out vec3 FragPos;

void main()
{
    Normal = mat3(transpose(inverse(modelViewMatrix))) * normals;
    gl_Position =  projectionMatrix * modelViewMatrix * position;
    FragPos = vec3(modelViewMatrix * position);
}
