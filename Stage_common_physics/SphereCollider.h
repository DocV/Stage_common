#pragma once
#ifndef SPHERECOLLIDER_H
#define SPHERECOLLIDER_H

#include "stdafx.h"
#include "Collider.h"
#include "Collisions.h"

namespace stage_common{
	class AABBCollider;

	class SphereCollider : public Collider{
	public:
		float radius;

		SphereCollider(float radius, glm::vec3 center) : radius(radius), Collider(center){}
		SphereCollider(const SphereCollider& other) : radius(other.radius), Collider(other.center){}
		SphereCollider& operator= (const SphereCollider& other){
			this->center = other.center;
			this->radius = other.radius;
			return *this;
		}

		Collider* copy() const{
			Collider* ret = new SphereCollider(*this);
			return ret;
		}

		bool checkCollision(const Collider& other) const{
			return other.checkCollision(*this);
		}
		bool checkCollision(const SphereCollider& other) const{
			return Collisions::collision_sphere_sphere(*this, other);
		}
		bool checkCollision(const AABBCollider& other) const{
			return Collisions::collision_sphere_aabb(*this, other);
		}

		glm::vec3 getCollisionNormal(const Collider& other, const glm::vec3& v) const{
			return glm::normalize(other.center - v - center);
		}

		virtual float minX() const{
			return center.x - radius;
		}
		virtual float minY() const{
			return center.y - radius;
		}
		virtual float minZ() const{
			return center.z - radius;
		}
		virtual float maxX() const{
			return center.x + radius;
		}
		virtual float maxY() const{
			return center.y + radius;
		}
		virtual float maxZ() const{
			return center.z + radius;
		}
	};
}

#endif