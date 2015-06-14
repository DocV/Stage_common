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

		bool checkCollision(const Collider& other) const{
			return other.checkCollision(*this);
		}
		bool checkCollision(const SphereCollider& other) const{
			return collision_sphere_sphere(*this, other);
		}
		bool checkCollision(const AABBCollider& other) const{
			return collision_sphere_aabb(*this, other);
		}
	};
}

#endif