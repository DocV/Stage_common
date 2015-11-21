#pragma once
#ifndef AABBCOLLIDER_H
#define AABBCOLLIDER_H

#include "stdafx.h"
#include "Collider.h"
#include "Collisions.h"

namespace stage_common{
	class SphereCollider;
	/** Luokka, joka mallintaa pelimaailman akselien suuntaisen 3D-laatikon (Axis-aligned bounding box)
	törmäysten tunnistamista varten
	*/
	class AABBCollider : public Collider{
	public:
		/** Laatikon koko, eli se, miten kauas keskipisteestään laatikko ylettyy jokaista 3D-maailman akselia pitkin*/
		glm::vec3 size;
		/** Luo uuden AABB-törmäyshahmon
		@param size		Laatikon kokoa kuvaava vektori, eli miten kauas keskipisteestä laatikko ylettyy eri akseleita pitkin
		@param center	Laatikon keskipisteen sijainti 3D-avaruudessa
		*/
		AABBCollider(glm::vec3 size, glm::vec3 center) : size(size), Collider(center){}
		/** Luo kopion AABB-törmäyshahmosta
		@param other	Kopioitava törmäyshahmo
		*/
		AABBCollider(const AABBCollider& other) : size(other.size), Collider(other.center){}
		/** Asettaa tämän törmäyshahmon tilan vastaamaan toista AABB-törmäyshahmoa
		@param other	Kopioitava törmäyshahmo
		@returns		Viite tähän törmäyshahmoon
		*/
		AABBCollider& operator= (const AABBCollider& other){
			this->center = other.center;
			this->size = other.size;
			return *this;
		}
		/** Virtuaalikopiometodi, joka luo kopion tästä törmäyshahmosta
		@returns	Osoitin luotuun kopioon. Huom: tuhottava manuaalisesti deletellä
		*/
		Collider* copy() const{
			Collider* ret = new AABBCollider(*this);
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
			return Collisions::collision_sphere_aabb(other, *this);
		}
		/** Tarkistaa, onko tämä törmäyshahmo törmännyt AABB-törmäyshahmoon
		@param other	AABB-törmäyshahmo
		@param returns	Palauttaa True, jos törmäyshahmot ovat törmänneet
		*/
		bool checkCollision(const AABBCollider& other) const{
			return Collisions::collision_aabb_aabb(*this, other);
		}
		/** Laskee kahden törmäyshahmon törmäyskohdan normaalin
		@param other	Toinen törmäyshahmo
		@param v		Toisen törmäyshahmon nopeus ennen törmäystä
		@param returns	Vektori, joka kuvaa törmäyshahmojen törmäyspinnan normaalia
		*/
		glm::vec3 getCollisionNormal(const Collider& other, const glm::vec3& v) const{
			//Tallennetaan liikesuunta vektoriin, jotta tiedetään mitkä laatikon reunat voivat osallistua törmäykseen
			glm::vec3 signs;
			for (int i = 0; i < 3; i++){
				signs[i] = (v[i] < 0 ? -1 : 1);
			}
			//Tämän törmäyshahmon kulma, joka on toisen törmäyshahmon sisässä			
			glm::vec3 thisCorner;
			//Toisen törmäyshahmon kulma, joka on tämän törmäyshahmon sisässä
			glm::vec3 otherCorner;
			thisCorner.x = (signs.x < 0 ? maxX() : minX());
			thisCorner.y = (signs.y < 0 ? maxY() : minY());
			thisCorner.z = (signs.z < 0 ? maxZ() : minZ());
			otherCorner.x = (signs.x < 0 ? other.maxX() : other.minX()) - v.x;
			otherCorner.y = (signs.y < 0 ? other.maxY() : other.minY()) - v.y;
			otherCorner.z = (signs.z < 0 ? other.maxZ() : other.minZ()) - v.z;
			//Kulmien etäisyys toisistaan ennen törmäystä
			glm::vec3 distance = (thisCorner - otherCorner) * signs;
			glm::vec3 normal;
			//Törmäysnormaali on todennäköisimmin pisimmän etäisyysakselin suuntainen
			if (distance.x > distance.y && distance.x > distance.z)	normal = glm::vec3(-1, 0, 0);
			else if (distance.y > distance.z) normal = glm::vec3(0, -1, 0);
			else normal = glm::vec3(0, 0, -1);
			return (normal * signs);
		}
		/** Palauttaa tämän törmäyshahmon pienimmän x-koordinaatin
		@returns	Tämän törmäyshahmon pienin x-koordinaatti
		*/
		virtual float minX() const{
			return center.x - size.x;
		}
		/** Palauttaa tämän törmäyshahmon pienimmän y-koordinaatin
		@returns	Tämän törmäyshahmon pienin y-koordinaatti
		*/
		virtual float minY() const{
			return center.y - size.y;
		}
		/** Palauttaa tämän törmäyshahmon pienimmän z-koordinaatin
		@returns	Tämän törmäyshahmon pienin z-koordinaatti
		*/
		virtual float minZ() const{
			return center.z - size.z;
		}
		/** Palauttaa tämän törmäyshahmon suurimman x-koordinaatin
		@returns	Tämän törmäyshahmon suurin x-koordinaatti
		*/
		virtual float maxX() const{
			return center.x + size.x;
		}
		/** Palauttaa tämän törmäyshahmon suurimman y-koordinaatin
		@returns	Tämän törmäyshahmon suurin y-koordinaatti
		*/
		virtual float maxY() const{
			return center.y + size.y;
		}
		/** Palauttaa tämän törmäyshahmon suurimman z-koordinaatin
		@returns	Tämän törmäyshahmon suurin z-koordinaatti
		*/
		virtual float maxZ() const{
			return center.z + size.z;
		}
	};
}
#endif