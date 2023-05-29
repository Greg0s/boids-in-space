#version 330 core
out vec4 FragColor;

in vec3 TexCoords;

uniform samplerCube cubemap;

void main() {    
    FragColor = texture(cubemap, TexCoords);
    //FragColor = vec4(0.0,1.0,0.0,1.0);
}