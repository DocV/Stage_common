#include "stdafx.h"
#include "Camera.h"
#include <glm\gtc\matrix_transform.hpp>

using namespace stage_common;

Camera::Camera(){
	projection = glm::perspective(45.0f, 4.0f / 3.0f, 0.1f, 100.0f);
	view = glm::lookAt(
		glm::vec3(0, 0, 0),
		glm::vec3(0, 0, -1),
		glm::vec3(0, 1, 0)
	);
}

Camera::Camera(glm::mat4& initialProjection, glm::mat4& initialView): projection(initialProjection), view(initialView){

}

void Camera::setProjectionMatrix(const glm::mat4& newProjection){
	projection = newProjection;
}

void Camera::setViewMatrix(const glm::mat4& newView){
	view = newView;
}