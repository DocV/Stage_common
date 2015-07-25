#ifndef GRAPHICSCONTROLLLER_H
#define GRAPHICSCONTROLLLER_H

#include "stdafx.h"
#include <string>
#include <vector>
#include "Model.h"
#include "Camera.h"

namespace stage_common{
	class Input;
	/** Luokka, joka toimii rajapintana pelimoottorin ja OpenGL:n välillä.
	Initialisoi OpenGL:n ja grafiikka-apukirjastot ja siirtää dataa moottorilta näytönohjaimelle.
	*/
	class GraphicsController{
	public:
		/** Käynnistää pelimoottorin grafiikkakomponentin ja luo uuden ikkunan.
		@param windowName	Ikkunan nimi
		@param xres			Ikkunan vaakaresoluutio
		@param yres			Ikkunan pystyresoluutio
		*/
		GraphicsController(std::string& windowName, int xres, int yres);

		/** Sammuttaa pelimoottorin grafiikkakomponentin, sulkee ikkunan ja sammuttaa grafiikka-apukirjastot.
		*/
		~GraphicsController();

		/** Määrittää 3D-mallin piirrettäväksi seuraavassa ruudunpäivityksessä.
		@param model	Osoitin piirrettävään 3D-malliin
		@param position	Matriisi, joka ilmaisee mihin, miten päin ja missä mittakaavassa malli piirretään
		*/
		void queue(const Model* model, const glm::mat4& position){
			//Sijoitettu headeriin oudon linkkaajabugin vuoksi
			if (drawCount >= models.size()){
				//Varataan tila uudelle mallille, jos sitä ei ennestään ole
				models.push_back(model);
				positions.push_back(position);
			}
			else {
				//Jos mallille on tilaa (jossain edellisessä ruudussa on piirretty ainakin yhtä monta mallia), käytetään hyväksi
				//olemassaolevaa tilanvarausta.
				models[drawCount] = model;
				positions[drawCount] = position;
			}
			drawCount++;
		}

		/** Piirtää ruudulle kaikki ne 3D-mallit, jotka on queue-metodilla tilattu pirrettäväksi edellisen draw-kutsun jälkeen.
		@param cam	Viite kameraolioon, jonka perspektiivistä mallit piirretään
		*/
		void draw(const Camera& cam);

		/** Kertoo, onko käyttäjä pyytänyt ohjelmaa pysähtymään.
		@returns	True, jos ohjelman suoritus tulisi pysäyttää
		*/
		bool shouldStop(){ return stopLoop; }

		/** Hakee globaalin GraphicsController-singletonin, jonka kautta kaikki piirtokutsut tulisi reitittää
		@returns	Osoitin GraphicsController-singletoniin
		*/
		static GraphicsController* getGlobalController();
	private:
		/** Osoitin globaaliin GraphicsController-singletoniin
		*/
		static GraphicsController* globalController;

		/** Osoitin olioon, joka pitää kirjaa nykyisen ruudunpäivityksen aikana luetuista syötteistä
		*/
		Input* input;

		/** True, jos ohjelman suoritus tulisi pysäyttää
		*/
		bool stopLoop = false;	

		/** Osoitin pelin ikkuna-olioon
		*/
		GLFWwindow* window;

		/** Lista seuraavan ruudunpäivityksen aikana piirrettävistä 3D-malleista
		*/
		std::vector<const Model*> models;

		/** Lista sijainneista, joihin seuraavan ruudunpäivityksen aikana piirretään 3D-malli
		*/
		std::vector<const glm::mat4> positions;

		/** Seuraavan ruudunpäivityksen aikana piirrettävien 3D-mallien lukumäärä
		*/
		unsigned int drawCount = 0;
	};

	
}

#endif