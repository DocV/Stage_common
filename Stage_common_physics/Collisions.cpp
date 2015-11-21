#include "stdafx.h"
#include "Collider.h"
#include "Collisions.h"
#include "SphereCollider.h"
#include "AABBCollider.h"
#include <iostream>

using namespace stage_common;

bool Collisions::collision_sphere_sphere(const SphereCollider& a, const SphereCollider& b){
	return glm::length(a.center - b.center) < (a.radius + b.radius);
}
bool Collisions::collision_sphere_aabb(const SphereCollider& a, const AABBCollider& b){
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
	return (squaredDistance <= a.radius * a.radius);
}
bool Collisions::collision_aabb_aabb(const AABBCollider& a, const AABBCollider& b){
	//Ovatko keskikohdat lähenpänä kuin laatikoiden koko?
	return
		glm::abs(a.center.x - b.center.x) < (a.size.x + b.size.x) &&
		glm::abs(a.center.y - b.center.y) < (a.size.y + b.size.y) &&
		glm::abs(a.center.z - b.center.z) < (a.size.z + b.size.z);
}
void Collisions::collisionVelocityChange(glm::vec3& v1, float m1, glm::vec3& v2, float m2){
	glm::vec3 res1 = (v1 * (m1 - m2) + 2 * m2 * v2) / (m1 + m2);
	glm::vec3 res2 = (v2 * (m2 - m1) + 2 * m1 * v1) / (m1 + m2);
	v1 = res1;
	v2 = res2;
}
void Collisions::backOff(Collider& mover, glm::vec3& velocity, const Collider& hit){
	while (mover.checkCollision(hit)){
		mover.center = mover.center - velocity;
	}
}
glm::vec3 Collisions::reflect(glm::vec3& v, glm::vec3 normal){
	return (-2 * (glm::dot(v, normal)) * normal + v);
}