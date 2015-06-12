#pragma once
#ifndef AABBCOLLIDER_H
#define AABBCOLLIDER_H

#include "stdafx.h"
#include "Collider.h"
#include "Collisions.h"

namespace stage_common{
	class SphereCollider;

	class AABBCollider : public Collider{
	public:
		glm::vec3 size;
		glm::vec3 center;
		bool checkCollision(const Collider& other){
			return other.checkCollision(*this);
		}
		bool checkCollision(const SphereCollider& other){
			return collision_sphere_aabb(other, *this);
		}
		bool checkCollision(const AABBCollider& other){
			return collision_aabb_aabb(*this, other);
		}
	};
}

#endif