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
	protected:
		glm::mat4 transform;
	};
}

#endif