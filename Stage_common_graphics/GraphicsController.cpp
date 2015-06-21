#include "stdafx.h"
#include "GraphicsController.h"
#include <iostream>
#include <Input.h>

using namespace stage_common;

GraphicsController* GraphicsController::globalController = nullptr;

GraphicsController::GraphicsController(std::string& windowName, int xres, int yres){
	// Ei sallita enempää kuin 1 GraphicsController
	if (globalController != nullptr){
		std::cout << "global graphics controller already set\n";
		abort(); 
	}
	globalController = this;

	// Käynnistetään GLFW
	if (!glfwInit()){
		std::cout << "failed to init glfw\n";
		abort();
	}

	glfwWindowHint(GLFW_CLIENT_API, GLFW_OPENGL_API);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_COMPAT_PROFILE);
	
	//Luodaan ikkuna
	window = glfwCreateWindow(xres, yres, windowName.c_str(), NULL, NULL);
	if (!window){
		std::cout << "failed to create window\n";
		glfwTerminate();
		abort();
	}	

	input = new Input(window);

	//Tehdään OpenGL-operaatiot tässä ikkunassa
	glfwMakeContextCurrent(window);
	//vsync
	glfwSwapInterval(1);

	//Käynnistetään GLEW
	if (glewInit()){
		std::cout << "failed to init glew\n";
		glfwDestroyWindow(window);
		glfwTerminate();
		abort();
	}
	
	//backface culling
	glEnable(GL_CULL_FACE);
	//Täytetään tyhjät alueet sinisellä
	glClearColor(0.0f, 0.0f, 0.4f, 0.0f);

	//Ei piirretä takana olevia polygoneja eteen
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LESS);

}

GraphicsController::~GraphicsController(){
	//std::cout << "gc stopping\n";
	globalController = nullptr;
	delete input;
	glfwDestroyWindow(window);
	glfwTerminate();
}

GraphicsController* GraphicsController::getGlobalController(){
	return globalController;
}

//Siirretty headeriin linkkaajabugin vuoksi
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
	//Tyhjennetään grafiikkapuskuri
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	//piirretään kaikki tilatut mallit
	for (unsigned int i = 0; i < drawCount; i++){
		models[i]->draw(cam, positions[i]);
	}
	//resetoidaan piirrettävien mallien määrä seuraavaa ruutua varten
	drawCount = 0;

	glfwSwapBuffers(window);
	glfwPollEvents();
	if (glfwWindowShouldClose(window)) stopLoop = true;
}