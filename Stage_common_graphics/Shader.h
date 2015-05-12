#ifndef SHADER_H
#define SHADER_H

#include "stdafx.h"
#include "Model.h"
#include "Camera.h"

namespace stage_common{
	class Shader{
	public:
		Shader(const char* vertexShader, const char* fragmentShader);
		virtual void draw(const Model& model, const Camera& cam, glm::mat4& modelMatrix) = 0;
	protected:
		GLuint program;
	};
}

#endif