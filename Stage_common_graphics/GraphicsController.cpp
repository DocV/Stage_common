#include "stdafx.h"
#include "GraphicsController.h"
#include <iostream>

using namespace stage_common;

GraphicsController* GraphicsController::globalController = nullptr;

GraphicsController::GraphicsController(std::string& windowName, int xres, int yres){
	std::cout << "starting gc\n";
	if (globalController != nullptr){
		std::cout << "gc already set\n";
		return; 
	}
	globalController = this;

	if (!glfwInit()){
		std::cout << "failed to init glfw\n";
		return; 
	}
	
	window = glfwCreateWindow(xres, yres, windowName.c_str(), NULL, NULL);
	if (!window){
		std::cout << "failed to create window\n";
		glfwTerminate();
		return;
	}	

	glfwMakeContextCurrent(window);
	glfwSwapInterval(1);

	if (glewInit()){
		std::cout << "failed to init glew\n";
		glfwTerminate();
		return;
	}
	
	glEnable(GL_CULL_FACE);
	glClearColor(0.0f, 0.0f, 0.4f, 0.0f);

	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LESS);

	models = std::vector<const Model*>();
	std::cout << "gc started\n";
}

GraphicsController::~GraphicsController(){
	std::cout << "gc stopping\n";
	globalController = nullptr;
	glfwTerminate();
}

GraphicsController* GraphicsController::getGlobalController(){
	return globalController;
}

/*void GraphicsController::queue(const Model* model, const glm::mat4& position){
	if (drawCount >= models.size()){
		models.push_back(model);
		positions.push_back(position);
	}
	else {
		models[drawCount] = model;
		positions[drawCount] = position;
	}
	drawCount++;
}*/

void GraphicsController::draw(const Camera& cam){
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	for (unsigned int i = 0; i < drawCount; i++){
		models[i]->draw(cam, positions[i]);
	}
	drawCount = 0;
	glfwSwapBuffers(window);
	glfwPollEvents();
}