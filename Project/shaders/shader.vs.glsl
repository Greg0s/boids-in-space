#version 330

layout(location = 0) in vec3 aVertexPosition;
layout(location = 1) in vec3 aVertexColor;

out vec3 vColor;

// var qui vont recevoir les matrices
// matrices calculées dans c++, on les envoi vers shaders qui les utilise pour calculer vertices
uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

void main() {
    vColor = aVertexColor;
    gl_Position = projection * view * model * vec4(aVertexPosition, 1);
}