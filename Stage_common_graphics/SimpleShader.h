#ifndef SIMPLESHADER_H
#define SIMPLESHADER_H

#include "stdafx.h"
#include "Shader.h"

namespace stage_common{
	class SimpleShader : public Shader {
	public:
		SimpleShader();
		void draw(const Model& model, const Camera& cam, glm::mat4& modelMatrix);
	private:
		GLuint matrixID;
	};
}

#endif