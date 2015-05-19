//Pikselisävytin
#version 330 core

//Parametri: värit
in vec3 fragmentColor;
//Palautetaan lasketut värit
out vec3 color;

void main(){
    color = fragmentColor;
}