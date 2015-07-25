#include "stdafx.h"
#include "Model.h"
#include "Shader.h"
#include <iostream>


using namespace stage_common;

Model::Model(std::vector<glm::vec3>& vertexData, std::vector<glm::vec3>& colorData,
	Shader* shader): vertexCount(vertexData.size()), shader(shader){
	//Ladataan OpenGL:n muistiin 3D-mallin verteksit
	glGenBuffers(1, &vertices);
	glBindBuffer(GL_ARRAY_BUFFER, vertices);
	glBufferData(GL_ARRAY_BUFFER, vertexData.size() * sizeof(glm::vec3), &vertexData[0], GL_STATIC_DRAW);

	//Ladataan OpenGL:n muistiin 3D-mallin verteksien värit
	glGenBuffers(1, &colors);
	glBindBuffer(GL_ARRAY_BUFFER, colors);
	glBufferData(GL_ARRAY_BUFFER, colorData.size() * sizeof(glm::vec3), &colorData[0], GL_STATIC_DRAW);

}

void Model::draw(const Camera& cam, glm::mat4& modelMatrix) const{
	shader->draw(*this, cam, modelMatrix);
}