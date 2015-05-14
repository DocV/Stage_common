#ifndef GRAPHICSCONTROLLLER_H
#define GRAPHICSCONTROLLLER_H

#include "stdafx.h"
#include <string>
#include <vector>
#include "Model.h"
#include "Camera.h"

namespace stage_common{
	
	class GraphicsController{
	public:
		GraphicsController(std::string& windowName, int xres, int yres);
		~GraphicsController();

		void queue(const Model* model, const glm::mat4& position){
			if (drawCount >= models.size()){
				models.push_back(model);
				positions.push_back(position);
			}
			else {
				models[drawCount] = model;
				positions[drawCount] = position;
			}
			drawCount++;
		}
		/*void linkerWorkaround(const Model* mod, const glm::mat4& mat){
			queue(mod, mat);
		}*/
		void draw(const Camera& cam);
		static GraphicsController* getGlobalController();
		bool stopLoop = false;
	private:
		static GraphicsController* globalController;
		GLFWwindow* window;
		std::vector<const Model*> models;
		std::vector<const glm::mat4> positions;
		unsigned int drawCount = 0;
	};

	
}

#endif