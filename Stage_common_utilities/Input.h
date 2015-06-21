#ifndef INPUT_H
#define INPUT_H

#include "stdafx.h"
#include <GLFW\glfw3.h>
#include <list>
#include <unordered_map>

namespace stage_common{
	class Input{
		friend class GraphicsController;
	public:
		void update(bool resetMouse){
			for (int i = 0; i < keys.size(); i++){
				lastInputs[keys[i]] = (glfwGetKey(window, keys[i]) == GLFW_PRESS);
			}
			glfwGetCursorPos(window, &cursorx, &cursory);
			glfwGetWindowSize(window, &xres, &yres);
			if (resetMouse){				
				glfwSetCursorPos(window, xres / 2, yres / 2);
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
			return cursorx / xres;
		}

		double getCursorY(){
			return cursory / yres;
		}

		static Input& getSingleton(){
			return *singleton;
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
		double cursorx, cursory;
		int xres, yres;
	};
}

#endif