#ifndef SHADER_H
#define SHADER_H

#include "stdafx.h"
#include "Model.h"
#include "Camera.h"

namespace stage_common{
	/** Abstrakti luokka, joka mallintaa OpenGL-sävytinohjelman
	*/
	class Shader{
	public:
		/** Lataa muistiin uuden sävytinohjelman
		@param vertexShader		Ohjelman verteksisävytin
		@param fragmentShader	Ohjelman pikselisävytin
		*/
		Shader(const char* vertexShader, const char* fragmentShader);
		/** Abstrakti metodi, joka piirtää mallin ruudulle tämän sävytinohjelman avulla
		@param model		Piirrettävä 3D-malli
		@param cam			Kamera, jonka kuvakulmasta malli piirretään
		@param modelMatrix	Matriisi, joka ilmaisee mihin malli piirretään
		*/
		virtual void draw(const Model& model, const Camera& cam, glm::mat4& modelMatrix) = 0;
	protected:
		/** Ilmaisee sävytinohjelman osoitteen OpenGL:n muistissa
		*/
		GLuint program;
	};
}

#endif