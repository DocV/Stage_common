#ifndef COLLISIONS_H
#define COLLISIONS_H

#include "stdafx.h"
#include <glm\glm.hpp>

namespace stage_common{
	class SphereCollider;
	class AABBCollider;
	class Collider;
	/** Apuluokka, joka sisältää staattisia funktioita fysiikkamoottorin laskelmien suorittamiseksi
	*/
	class Collisions{
	public:
		/** Laskee, onko pallotörmäyshahmo törmännyt toiseen
		@param a	Pallotörmäyshahmo
		@param b	Toinen pallotörmäyshahmo
		@returns	True, jos törmäyshahmot ovat törmänneet
		*/
		static bool collision_sphere_sphere(const SphereCollider& a, const SphereCollider& b);
		/** Laskee, onko pallotörmäyshahmo törmännyt AABB-törmäyshahmoon
		@param a	Pallotörmäyshahmo
		@param b	AABB-törmäyshahmo
		@returns	True, jos törmäyshahmot ovat törmänneet
		*/
		static bool collision_sphere_aabb(const SphereCollider& a, const AABBCollider& b);
		/** Laskee, onko AABB-törmäyshahmo törmännyt toiseen
		@param a	AABB-törmäyshahmo
		@param b	Toinen AABB-törmäyshahmo
		@returns	True, jos törmäyshahmot ovat törmänneet
		*/
		static bool collision_aabb_aabb(const AABBCollider& a, const AABBCollider& b);
		/** Siirtää törmäyksen jälkeen törmäyshahmoa taaksepäin, kunnes se ei enää ole törmäyksessä toisen kanssa
		@param mover	Taaksepäin siirtyvä törmäyshahmo
		@param velocity	Siirtyvän törmäyshahmon nopeus
		@param hit		Törmäyshahmo, johon mover törmäsi
		*/
		static void backOff(Collider& mover, glm::vec3& velocity, const Collider& hit);
		/** Laskee törmänneille kappaleille uudet nopeudet
		@param v1	Ensimmäisen kappaleen nopeus
		@param m1	Ensimmäisen kappaleen massa
		@param v2	Toisen kappaleen nopeus
		@param m2	Toisen kappaleen massa
		*/
		static void collisionVelocityChange(glm::vec3& v1, float m1, glm::vec3& v2, float m2);
		/** "Kimmottaa" kappaleen pinnasta, eli laksee uuden nopeuden, kun kappale törmää liikkumattomaan pintaan
		@param v		Kappaleen nopeus
		@param normal	Törmäyspinnan normaali
		@returns		Kappaleen nopeus törmäyksen jälkeen
		*/
		static glm::vec3 reflect(glm::vec3& v, glm::vec3 normal);
	};	
}
#endif