#include "stdafx.h"
#include "Model.h"
#include "Utilities.h"
#include "Shader.h"
#include <iostream>


using namespace stage_common;

Model::Model(std::vector<glm::vec3>& vertexData, unsigned int vertexCount, std::vector<glm::vec3>& colorData,
	Shader* shader): vertexCount(vertexCount), shader(shader){
	glGenBuffers(1, &vertices);
	glBindBuffer(GL_ARRAY_BUFFER, vertices);
	glBufferData(GL_ARRAY_BUFFER, vertexData.size() * sizeof(glm::vec3), &vertexData[0], GL_STATIC_DRAW);

	glGenBuffers(1, &colors);
	glBindBuffer(GL_ARRAY_BUFFER, colors);
	glBufferData(GL_ARRAY_BUFFER, colorData.size() * sizeof(glm::vec3), &colorData[0], GL_STATIC_DRAW);

}

void Model::draw(const Camera& cam, glm::mat4& modelMatrix) const{
	shader->draw(*this, cam, modelMatrix);
}