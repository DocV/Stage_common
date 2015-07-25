#ifndef COLLIDER_H
#define COLLIDER_H

#include "stdafx.h"
#include <glm\glm.hpp>

namespace stage_common{
	class SphereCollider;
	class AABBCollider;

	/** Abstrakti luokka, joka mallintaa törmäyshahmon törmäysten tunnistamista varten
	*/
	class Collider{
	public:
		/** Tämän törmäyshahmon keskipiste 3D-avaruudessa
		*/
		glm::vec3 center;

		/** Luo uuden törmäyshahmon
		@param center	Törmäyshahmon keskipiste 3D-avaruudessa
		*/
		Collider(glm::vec3 center) : center(center){}

		/** Tarkistaa, onko tämä törmäyshahmo törmännyt toiseen
		@param other	Toinen törmäyshahmo
		@param returns	Palauttaa True, jos törmäyshahmot ovat törmänneet
		*/
		virtual bool checkCollision(const Collider& other) const = 0;

		/** Tarkistaa, onko tämä törmäyshahmo törmännyt pallotörmäyshamoon
		@param other	Pallotörmäyshahmo
		@param returns	Palauttaa True, jos törmäyshahmot ovat törmänneet
		*/
		virtual bool checkCollision(const SphereCollider& other) const = 0;

		/** Tarkistaa, onko tämä törmäyshahmo törmännyt AABB-törmäyshahmoon
		@param other	AABB-törmäyshahmo
		@param returns	Palauttaa True, jos törmäyshahmot ovat törmänneet
		*/
		virtual bool checkCollision(const AABBCollider& other) const = 0;

		/** Virtuaalikopiometodi, joka luo kopion tästä törmäyshahmosta
		@returns	Osoitin luotuun kopioon. Huom: tuhottava manuaalisesti deletellä
		*/
		virtual Collider* copy() const = 0;

		/** Laskee kahden törmäyshahmon törmäyskohdan normaalin
		@param other	Toinen törmäyshahmo
		@param v		Toisen törmäyshahmon nopeus ennen törmäystä
		@param returns	Vektori, joka kuvaa törmäyshahmojen törmäysnormaalia
		*/
		virtual glm::vec3 getCollisionNormal(const Collider& other, const glm::vec3& v) const = 0;

		/** Palauttaa tämän törmäyshahmon pienimmän x-koordinaatin
		@returns	Tämän törmäyshahmon pienin x-koordinaatti
		*/
		virtual float minX() const = 0;

		/** Palauttaa tämän törmäyshahmon pienimmän y-koordinaatin
		@returns	Tämän törmäyshahmon pienin y-koordinaatti
		*/
		virtual float minY() const = 0;

		/** Palauttaa tämän törmäyshahmon pienimmän z-koordinaatin
		@returns	Tämän törmäyshahmon pienin z-koordinaatti
		*/
		virtual float minZ() const = 0;

		/** Palauttaa tämän törmäyshahmon suurimman x-koordinaatin
		@returns	Tämän törmäyshahmon suurin x-koordinaatti
		*/
		virtual float maxX() const = 0;

		/** Palauttaa tämän törmäyshahmon suurimman y-koordinaatin
		@returns	Tämän törmäyshahmon suurin y-koordinaatti
		*/
		virtual float maxY() const = 0;

		/** Palauttaa tämän törmäyshahmon suurimman z-koordinaatin
		@returns	Tämän törmäyshahmon suurin z-koordinaatti
		*/
		virtual float maxZ() const = 0;
	};
}

#endif