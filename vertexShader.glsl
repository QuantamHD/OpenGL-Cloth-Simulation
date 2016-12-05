#version 330 core

layout (location = 0) in vec4 position;
layout (location = 1) in vec3 normals;

uniform mat4 modelViewMatrix;
uniform mat4 projectionMatrix;

out vec3 vertexColor;

void main()
{
    vertexColor = vec3(normals.x, normals.y, normals.z);
    gl_Position =  projectionMatrix * modelViewMatrix * position;
}
