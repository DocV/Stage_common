#ifndef INPUT_H
#define INPUT_H

#include "stdafx.h"
#include <GLFW\glfw3.h>
#include <list>
#include <unordered_map>
#include <iostream>

namespace stage_common{
	class Input{
		friend class GraphicsController;
	public:
		void update(bool rm){
			for (int i = 0; i < keys.size(); i++){
				lastInputs[keys[i]] = (glfwGetKey(window, keys[i]) == GLFW_PRESS);
			}
			glfwGetCursorPos(window, &cursorx, &cursory);
			glfwGetWindowSize(window, &xres, &yres);
			if (rm){				
				resetMouse();
			}
		}
		void registerKey(int key){
			if (lastInputs.count(key) == 0){
				keys.push_back(key);
				lastInputs.emplace(key, false);
			}
		}
		bool getKeyDown(int key){
			return lastInputs[key];
		}

		double getCursorX(){
			return cursorx / (double)xres;
		}

		double getCursorY(){
			return cursory / (double)yres;
		}

		static Input& getSingleton(){
			return *singleton;
		}

		void resetMouse(){
			glfwSetCursorPos(window, xres / 2, yres / 2);
		}
	private:
		Input(GLFWwindow* window) : window(window){
			singleton = this;
		}
		~Input(){
			if (singleton == this) singleton = nullptr;
		}
		static Input* singleton;
		GLFWwindow* window;
		std::vector<int> keys;
		std::unordered_map<int, bool> lastInputs;
		double cursorx = 1, cursory = 1;
		int xres = 2, yres = 2;
	};
}

#endif