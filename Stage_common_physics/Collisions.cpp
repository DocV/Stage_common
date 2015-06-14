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

static void collisionVelocityChange(glm::vec3& v1, float m1, glm::vec3& v2, float m2){
	glm::vec3 res1 = (v1 * (m1 - m2) + 2 * m2 * v2) / (m1 + m2);
	glm::vec3 res2 = (v2 * (m2 - m1) + 2 * m1 * v1) / (m1 + m2);
	v1 = res1;
	v2 = res2;
}


static void backOff(Collider& mover, glm::vec3& velocity, const Collider& hit, unsigned int resolution){
	if (!mover.checkCollision(hit)){
		return;
	}
	glm::vec3 start = mover.center - velocity;
	glm::vec3 end = mover.center;
	for (unsigned int i = 0; i < resolution; i++){
		glm::vec3 midpoint = (start + end) / 2.0f;
		mover.center = midpoint;
		if (mover.checkCollision(hit)){
			end = midpoint;
		}
		else {
			start = midpoint;
		}
	}
	mover.center = start;
}