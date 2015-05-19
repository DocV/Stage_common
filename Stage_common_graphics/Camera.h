#ifndef CAMERA_H
#define CAMERA_H

#include "stdafx.h"


namespace stage_common{
	/**
	Luokka, joka sisältää grafiikkamoottorin kameran mallintamiseen vaadittavat tiedot.
	*/
	class Camera{
	public:
		/** Luo kameran oletusasetuksilla (45.0 asteen fov, kuvasuhde 4:3, piirtoetäisyys 0.1-100, suunnattu origoon)
		*/
		Camera();
		/** Luo kameran luojan määrittelemillä asetuksilla
		@param initialProjection	Kameran projektiomatriisi (fov, kuvasuhde, piirtoetäisyys) simulaation alussa 
		@param initialView			Kameran näkymämatriisi (mihin kamera on suunnattu) simulaation alussa 
		*/
		Camera(glm::mat4& initialProjection, glm::mat4& initialView);
		/** Palauttaa kameran nykyisen projektiomatriisin
		@returns	Kameran projektiomatriisi
		*/
		glm::mat4 getProjectionMatrix() const{ return projection; }
		/** Palauttaa kameran nykyisen näkymämatriisin
		@returns	Kameran näkymämatriisi
		*/
		glm::mat4 getViewMatrix() const{ return view; }
		/** Asettaa kameralle uuden projektiomatriisin
		@param newProjection	Uusi projektiomatriisi
		*/
		void setProjectionMatrix(const glm::mat4& newProjection);
		/** Asettaa kameralle uuden näkymämatriisin
		@param newView	Uusi näkymämatriisi
		*/
		void setViewMatrix(const glm::mat4& newView);
	private:
		/** Kameran projektiomatriisi (fov, kuvasuhde, piirtoetäisyys)
		*/
		glm::mat4 projection;
		/** Kameran näkymämatriisi (mihin kamera on suunnattu)
		*/
		glm::mat4 view;
	};
}

#endif