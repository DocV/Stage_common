#ifndef INPUT_H
#define INPUT_H

#include "stdafx.h"
#include <GLFW\glfw3.h>
#include <list>
#include <unordered_map>
#include <iostream>

namespace stage_common{
	/** Käyttäjän syötteitä lukeva luokka
	*/
	class Input{
		//Syötteiden lukemista varten tarvitaan osoitin peli-ikkunaan
		friend class GraphicsController;
	public:
		/** Hakee rekisteröityjen näppäimien nykytilan
		@param rm	Ilmaisee, palautetaanko hiiri ruudun keskelle
		*/
		void update(bool rm){
			//Haetaan kaikkien rekisteröityjen näppäinten tila
			for (int i = 0; i < keys.size(); i++){
				lastInputs[keys[i]] = (glfwGetKey(window, keys[i]) == GLFW_PRESS);
			}
			//Haetaan hiiriosoittimen sijainti ruudulla
			glfwGetCursorPos(window, &cursorx, &cursory);
			glfwGetWindowSize(window, &xres, &yres);
			if (rm){
				//Palautetaan hiiri keskelle ruutua
				resetMouse();
			}
		}

		/** Pyytää input-oliota tarkkailemaan halutun näppäimen tilaa
		@param key	Tarkkailtavan näppäimen GLFW-tunnus
		*/
		void registerKey(int key){
			if (lastInputs.count(key) == 0){
				keys.push_back(key);
				lastInputs.emplace(key, false);
			}
		}

		/** Kysyy, oliko tietty näppäin pohjassa tämän ruudunpäivityksen alussa
		@param key	Näppäimen GLFW-tunnus
		@returns	true, jos näppäin oli pohjassa
		*/
		bool getKeyDown(int key){
			return lastInputs[key];
		}

		/** Hakee hiiriosoittimen x-koordinaatin suhteessa peli-ikkunaan
		@returns	Arvo väliltä 0 (ruudun vasen reuna) - 1 (ruudun oikea reuna)
		*/
		double getCursorX(){
			return cursorx / (double)xres;
		}

		/** Hakee hiiriosoittimen y-koordinaatin suhteessa peli-ikkunaan
		@returns	Arvo väliltä 0 (ruudun yläreuna) - 1 (ruudun alareuna)
		*/
		double getCursorY(){
			return cursory / (double)yres;
		}

		/** Hakee osoittimen globaaliin Input-singletoniin
		@returns	Globaalin Input-olion osoite
		*/
		static Input& getSingleton(){
			return *singleton;
		}

		/** Asettaa hiiren keskelle peli-ikkunaa
		*/
		void resetMouse(){
			glfwSetCursorPos(window, xres / 2, yres / 2);
		}
	private:
		/**Luo uuden Input-olion
		@param window	Osoitin peli-ikkunaolioon
		*/
		Input(GLFWwindow* window) : window(window){
			singleton = this;
			//Piilotetaan hiiri, kun se on peli-ikkunan päällä
			glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_HIDDEN);
		}

		/** Tuhoaa Input-olion
		*/
		~Input(){
			if (singleton == this) singleton = nullptr;
		}

		/** Globaalin syötteidenhallintaolion osoite
		*/
		static Input* singleton;
		
		/** Peli-ikkunan osoite
		*/
		GLFWwindow* window;

		/** Lista niistä näppäimistä, joiden tilaa tarkkaillaan
		*/
		std::vector<int> keys;

		/** Lista tarkkailtavien näppäimien tiloista ruudunpäivityksen alussa
		*/
		std::unordered_map<int, bool> lastInputs;

		/** Hiiriosoittimen x- ja y-koordinaatit ruudunpäivityksen alussa
		*/
		double cursorx = 1, cursory = 1;

		/** Peli-ikkunan vaaka- ja pystyresoluutio
		*/
		int xres = 2, yres = 2;
	};
}

#endif