#ifndef MODEL_H
#define MODEL_H

#include "stdafx.h"
#include "Camera.h"
#include <vector>

namespace stage_common{
	class Shader;
	class Model{
	public:
		Model(std::vector<glm::vec3>& vertexData, unsigned int vertexCount, std::vector<glm::vec3>& colorData, Shader* shader);
		GLuint getVertices() const { return vertices; }
		GLuint getColors() const { return colors; }
		unsigned int getVertexCount() const { return vertexCount; }
		void draw(const Camera& cam, glm::mat4& modelMatrix) const;
	private:
		GLuint vertices;
		GLuint colors;
		Shader* shader;
		unsigned int vertexCount;
	};
}

#endif