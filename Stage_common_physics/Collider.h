#ifndef COLLIDER_H
#define COLLIDER_H

#include "stdafx.h"
#include <glm\glm.hpp>

namespace stage_common{
	class SphereCollider;
	class AABBCollider;

	class Collider{
	public:
		glm::vec3 center;

		Collider(glm::vec3 center) : center(center){}

		virtual bool checkCollision(const Collider& other) const = 0;
		virtual bool checkCollision(const SphereCollider& other) const = 0;
		virtual bool checkCollision(const AABBCollider& other) const = 0;
		virtual Collider* copy() const = 0;

		virtual glm::vec3 getCollisionNormal(const Collider& other, const glm::vec3& v) const = 0;
		virtual float minX() const = 0;
		virtual float minY() const = 0;
		virtual float minZ() const = 0;
		virtual float maxX() const = 0;
		virtual float maxY() const = 0;
		virtual float maxZ() const = 0;
	};
}

#endif