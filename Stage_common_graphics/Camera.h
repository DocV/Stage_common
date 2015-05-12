#ifndef CAMERA_H
#define CAMERA_H

#include "stdafx.h"


namespace stage_common{
	class Camera{
	public:
		Camera();
		Camera(glm::mat4& initialProjection, glm::mat4& initialView);
		glm::mat4 getProjectionMatrix() const{ return projection; }
		glm::mat4 getViewMatrix() const{ return view; }
		void setProjectionMatrix(const glm::mat4& newProjection);
		void setViewMatrix(const glm::mat4& newView);
	private:
		glm::mat4 projection;
		glm::mat4 view;
	};
}

#endif