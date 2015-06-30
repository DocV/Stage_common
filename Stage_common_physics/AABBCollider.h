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

		AABBCollider(glm::vec3 size, glm::vec3 center) : size(size), Collider(center){}
		AABBCollider(const AABBCollider& other) : size(other.size), Collider(other.center){}
		AABBCollider& operator= (const AABBCollider& other){
			this->center = other.center;
			this->size = other.size;
			return *this;
		}

		Collider* copy() const{
			Collider* ret = new AABBCollider(*this);
			return ret;
		}

		bool checkCollision(const Collider& other) const{
			return other.checkCollision(*this);
		}
		bool checkCollision(const SphereCollider& other) const{
			return Collisions::collision_sphere_aabb(other, *this);
		}
		bool checkCollision(const AABBCollider& other) const{
			return Collisions::collision_aabb_aabb(*this, other);
		}

		glm::vec3 getCollisionNormal(const Collider& other, const glm::vec3& v) const{
			glm::vec3 signs;
			for (int i = 0; i < 3; i++){
				signs[i] = (v[i] < 0 ? -1 : 1);
			}
			glm::vec3 thisCorner;
			glm::vec3 otherCorner;
			thisCorner.x = (signs.x < 0 ? maxX() : minX());
			thisCorner.y = (signs.y < 0 ? maxY() : minY());
			thisCorner.z = (signs.z < 0 ? maxZ() : minZ());
			otherCorner.x = (signs.x < 0 ? other.maxX() : other.minX()) - v.x;
			otherCorner.y = (signs.y < 0 ? other.maxY() : other.minY()) - v.y;
			otherCorner.z = (signs.z < 0 ? other.maxZ() : other.minZ()) - v.z;
			glm::vec3 distance = (thisCorner - otherCorner) * signs;
			glm::vec3 normal;
			if (distance.x > distance.y && distance.x > distance.z)	normal = glm::vec3(-1, 0, 0);
			else if (distance.y > distance.z) normal = glm::vec3(0, -1, 0);
			else normal = glm::vec3(0, 0, -1);
			return (normal * signs);
		}

		virtual float minX() const{
			return center.x - size.x;
		}
		virtual float minY() const{
			return center.y - size.y;
		}
		virtual float minZ() const{
			return center.z - size.z;
		}
		virtual float maxX() const{
			return center.x + size.x;
		}
		virtual float maxY() const{
			return center.y + size.y;
		}
		virtual float maxZ() const{
			return center.z + size.z;
		}
	};
}

#endif