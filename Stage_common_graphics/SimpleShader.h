#ifndef SIMPLESHADER_H
#define SIMPLESHADER_H

#include "stdafx.h"
#include "Shader.h"

namespace stage_common{
	/** Yksinkertainen sävytinohjelma, joka piirtää ja värittää tekstuurittoman 3D-mallin
	*/
	class SimpleShader : public Shader {
	public:
		/** Lataa sävytinohjelman
		*/
		SimpleShader();
		/** Metodi, joka piirtää mallin ruudulle tämän sävytinohjelman avulla
		@param model		Piirrettävä 3D-malli
		@param cam			Kamera, jonka kuvakulmasta malli piirretään
		@param modelMatrix	Matriisi, joka ilmaisee mihin malli piirretään
		*/
		void draw(const Model& model, const Camera& cam, glm::mat4& modelMatrix);
	private:
		/** Sävytinohjelman käyttämän muuttujan osoite
		*/
		GLuint matrixID;
	};
}

#endif