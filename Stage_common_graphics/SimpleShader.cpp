#include "stdafx.h"
#include "SimpleShader.h"

#include <glm\gtc\matrix_transform.hpp>
#include <iostream>

using namespace stage_common;

SimpleShader::SimpleShader() : Shader("simplevertexshader.glsl", "simplefragmentshader.glsl"){
	matrixID = glGetUniformLocation(program, "MVP");
}


void SimpleShader::draw(const Model& model, const Camera& cam, glm::mat4& modelMatrix){

	//Lasketaan mallin sijainti kameraan nähden
	glm::mat4 MVP = cam.getProjectionMatrix() * cam.getViewMatrix() * modelMatrix;

	glUseProgram(program);
	//Asetetaan mallin sijainti sävytinohjelman muuttujaan
	glUniformMatrix4fv(matrixID, 1, GL_FALSE, &MVP[0][0]);

	//Annetaan verteksit sävyttimelle
	glEnableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, model.getVertices());
	glVertexAttribPointer(
		0,                  // Parametri 0
		3,                  // koko
		GL_FLOAT,           // tyyppi
		GL_FALSE,           // normalisointi
		0,                  // alkioiden välinen etäisyys
		(void*)0            // ensimmäisen alkion offset
	);
	//Annetaan värit sävyttimelle
	glEnableVertexAttribArray(1);
	glBindBuffer(GL_ARRAY_BUFFER, model.getColors());
	glVertexAttribPointer(
		1,                                
		3,                                
		GL_FLOAT,                         
		GL_FALSE,                         
		0,                                
		(void*)0                          
	);
	//Piirretään polygonit
	glDrawArrays(GL_TRIANGLES, 0, model.getVertexCount());

	glDisableVertexAttribArray(0);
	glDisableVertexAttribArray(1);
}