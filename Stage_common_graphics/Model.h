#ifndef MODEL_H
#define MODEL_H

#include "stdafx.h"
#include "Camera.h"
#include <vector>

namespace stage_common{
	class Shader;

	/** Luokka, joka sisältää tiedot 3D-mallin piirtämistä varten.
	Jokaista eri 3D-mallia kohden tulisi olla tasan yksi Model-olio.
	*/
	class Model{
	public:
		/** Luo uuden 3D-mallin pelimoottorin muistiin.
		@param vertexData	Mallin verteksit listana kolmen koordinaatin vektoreita.
		@param colorData	Mallin verteksien värit listana kolmen väriarvon vektoreita.
		@param shader		Tämän mallin piirtämiseen kaytettävä sävytinolio.
		*/
		Model(std::vector<glm::vec3>& vertexData, std::vector<glm::vec3>& colorData, Shader* shader);
		/** Palauttaa sijainnin, jonne OpenGL on ladannut tämän mallin verteksit
		@returns	Mallin verteksien sijaintia kuvaava GLuint
		*/
		GLuint getVertices() const { return vertices; }
		/** Palauttaa sijainnin, jonne OpenGL on ladannut tämän mallin värit
		@returns	Mallin värien sijaintia kuvaava GLuint
		*/
		GLuint getColors() const { return colors; }
		/** Kertoo, miten monta verteksiä tässä mallissa on
		@returns	Verteksien lukumäärä
		*/
		unsigned int getVertexCount() const { return vertexCount; }
		/** Piirtää tämän 3D-mallin ruudulle
		@param cam			Kameraolio, jonka perspektiivistä malli piirretään
		@param modelMatrix	Mallin sijaintia, kiertoa ja skaalausta kuvaava matriisi
		*/
		void draw(const Camera& cam, glm::mat4& modelMatrix) const;
	private:
		/** Mallin verteksien sijaintia kuvaava GLuint
		*/
		GLuint vertices;
		/** Mallin värien sijaintia kuvaava GLuint
		*/
		GLuint colors;
		/** Osoitin sävytinolioon, jonka sävytinohjelmalla tämä malli piirretään
		*/
		Shader* shader;
		/** Mallin verteksien lukumäärä
		*/
		unsigned int vertexCount;
	};
}

#endif