#version 330 core

layout (location = 0) in vec4 position;
layout (location = 1) in vec3 normals;

uniform mat4 modelViewMatrix;
uniform mat4 projectionMatrix;

void main()
{
    gl_Position =  projectionMatrix * modelViewMatrix * position;
}
