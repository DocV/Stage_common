#ifndef COLLISIONS_H
#define COLLISIONS_H

#include "stdafx.h"

namespace stage_common{
	class SphereCollider;
	class AABBCollider;

	static bool collision_sphere_sphere(const SphereCollider& a, const SphereCollider& b);
	static bool collision_sphere_aabb(const SphereCollider& a, const AABBCollider& b);
	static bool collision_aabb_aabb(const AABBCollider& a, const AABBCollider& b);
}

#endif