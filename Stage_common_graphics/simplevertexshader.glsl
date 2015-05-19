//Verteksisävytin
#version 330 core

//1. parametri: verteksit
layout(location = 0) in vec3 vertexPosition_modelspace;
//2. parametri: värit
layout(location = 1) in vec3 vertexColor;

//Annetaan värit pikselisävyttimelle
out vec3 fragmentColor;

//Mallin sijainti suhteessa kameraan
uniform mat4 MVP;
 
//Lasketaan verteksin sijainti ruudulla suhteessa malliin ja annetaan värit pikselisävyttimelle
void main(){
    vec4 v = vec4(vertexPosition_modelspace,1);
    gl_Position = MVP * v;
	fragmentColor = vertexColor;
}