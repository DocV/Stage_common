#pragma once
#ifndef SPHERECOLLIDER_H
#define SPHERECOLLIDER_H

#include "stdafx.h"
#include "Collider.h"
#include "Collisions.h"

namespace stage_common{
	class AABBCollider;
	/** Luokka, joka mallintaa 3D-pallon törmäysten tunnistamista varten
	*/
	class SphereCollider : public Collider{
	public:
		/** Törmäyspallon säde
		*/
		float radius;
		/** Luo uuden pallotörmäyshahmon
		@param radius	Pallon säde
		@param center	Pallon keskipisteen sijainti 3D-avaruudessa
		*/
		SphereCollider(float radius, glm::vec3 center) : radius(radius), Collider(center){}
		/** Luo kopion pallotörmäyshahmosta
		@param other	Kopioitava törmäyshahmo
		*/
		SphereCollider(const SphereCollider& other) : radius(other.radius), Collider(other.center){}
		/** Asettaa tämän törmäyshahmon tilan vastaamaan toista pallotörmäyshahmoa
		@param other	Kopioitava törmäyshahmo
		@returns		Viite tähän törmäyshahmoon
		*/
		SphereCollider& operator= (const SphereCollider& other){
			this->center = other.center;
			this->radius = other.radius;
			return *this;
		}
		/** Virtuaalikopiometodi, joka luo kopion tästä törmäyshahmosta
		@returns	Osoitin luotuun kopioon. Huom: tuhottava manuaalisesti deletellä
		*/
		Collider* copy() const{
			Collider* ret = new SphereCollider(*this);
			return ret;
		}
		/** Tarkistaa, onko tämä törmäyshahmo törmännyt toiseen
		@param other	Toinen törmäyshahmo
		@param returns	Palauttaa True, jos törmäyshahmot ovat törmänneet
		*/
		bool checkCollision(const Collider& other) const{
			return other.checkCollision(*this);
		}
		/** Tarkistaa, onko tämä törmäyshahmo törmännyt pallotörmäyshamoon
		@param other	Pallotörmäyshahmo
		@param returns	Palauttaa True, jos törmäyshahmot ovat törmänneet
		*/
		bool checkCollision(const SphereCollider& other) const{
			return Collisions::collision_sphere_sphere(*this, other);
		}
		/** Tarkistaa, onko tämä törmäyshahmo törmännyt AABB-törmäyshahmoon
		@param other	AABB-törmäyshahmo
		@param returns	Palauttaa True, jos törmäyshahmot ovat törmänneet
		*/
		bool checkCollision(const AABBCollider& other) const{
			return Collisions::collision_sphere_aabb(*this, other);
		}
		/** Laskee kahden törmäyshahmon törmäyskohdan normaalin
		@param other	Toinen törmäyshahmo
		@param v		Toisen törmäyshahmon nopeus ennen törmäystä
		@param returns	Vektori, joka kuvaa törmäyshahmojen törmäysnormaalia
		*/
		glm::vec3 getCollisionNormal(const Collider& other, const glm::vec3& v) const{
			return glm::normalize(other.center - v - center);
		}
		/** Palauttaa tämän törmäyshahmon pienimmän x-koordinaatin
		@returns	Tämän törmäyshahmon pienin x-koordinaatti
		*/
		virtual float minX() const{
			return center.x - radius;
		}
		/** Palauttaa tämän törmäyshahmon pienimmän y-koordinaatin
		@returns	Tämän törmäyshahmon pienin x-koordinaatti
		*/
		virtual float minY() const{
			return center.y - radius;
		}
		/** Palauttaa tämän törmäyshahmon pienimmän z-koordinaatin
		@returns	Tämän törmäyshahmon pienin x-koordinaatti
		*/
		virtual float minZ() const{
			return center.z - radius;
		}
		/** Palauttaa tämän törmäyshahmon suurimman x-koordinaatin
		@returns	Tämän törmäyshahmon suurin x-koordinaatti
		*/
		virtual float maxX() const{
			return center.x + radius;
		}
		/** Palauttaa tämän törmäyshahmon suurimman y-koordinaatin
		@returns	Tämän törmäyshahmon suurin y-koordinaatti
		*/
		virtual float maxY() const{
			return center.y + radius;
		}
		/** Palauttaa tämän törmäyshahmon suurimman z-koordinaatin
		@returns	Tämän törmäyshahmon suurin z-koordinaatti
		*/
		virtual float maxZ() const{
			return center.z + radius;
		}
	};
}
#endif