#include "stdafx.h"
#include "Collisions.h"
#include "SphereCollider.h"
#include "AABBCollider.h"

using namespace stage_common;

static bool collision_sphere_sphere(const SphereCollider& a, const SphereCollider& b){
	return (a.center - b.center).length < (a.radius + b.radius);
}
static bool collision_sphere_aabb(const SphereCollider& a, const AABBCollider& b){
	//Arvo's algorithm
	float squaredDistance = 0;
	float diff = 0;
	
	//iteroidaan x,y,z
	for (int i = 0; i < 3; i++){
		if (a.center[i] < (b.center[i] - b.size[i])){
			diff = a.center[i] - (b.center[i] - b.size[i]);
			squaredDistance += diff * diff;
		}
		if (a.center[i] > (b.center[i] + b.size[i])){
			diff = a.center[i] - (b.center[i] + b.size[i]);
			squaredDistance += diff * diff;
		}
	}

	return (squaredDistance > a.radius);
}
static bool collision_aabb_aabb(const AABBCollider& a, const AABBCollider& b){
	return
		glm::abs(a.center.x - b.center.x) < (a.size.x + b.size.x) &&
		glm::abs(a.center.y - b.center.y) < (a.size.y + b.size.y) &&
		glm::abs(a.center.z - b.center.z) < (a.size.z + b.size.z);
}