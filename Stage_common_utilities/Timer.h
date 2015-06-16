#ifndef TIMER_H
#define TIMER_H

#include "stdafx.h"
#include <chrono>

typedef std::chrono::time_point<std::chrono::high_resolution_clock> clock_time;

namespace stage_common{
	/** Ajastinluokka, tarjoaa palvelun laskennassa kuluvan ajan mittaamiseen.
	Laskee mittauskutsujen välisten aikojen pituuksia ja soveltuu erityisesti toistuvien tapahtumien kuten pelimoottorin
	pelisilmukoiden pituuksien mittaamiseen.
	*/
	class Timer{
	public:
		/** Käynnistää ajastimen
		*/
		void start();
		/** Mittaa, kuinka paljon aikaa on kulunut edellisestä start()-kutsusta
		*/
		void stop();
		/** Mittaa, kuinka kauan on kulunut edellisestä start()-kutsusta ja käynnistää ajastimen uudestaan
		Käytännössa sama kuin stop(); start();
		*/
		void tick();
		/** Palauttaa tiedon siitä, kuinka paljon aikaa ajastin on olemassaolonsa aikana mitannut millisekunteina
		@returns	Ajastimen mittaama kokonaisaika (viimeisen stop() tai tick() -kutsun kohdalla)
		*/
		double totalTime(){ return totalms; }
		/** Palauttaa tiedon siitä, kuinka monta mittauspistettä ajastin on käsitellyt
		@returns	Kuinka monta stop() tai tick() -kutsua ajastin on käsitellyt
		*/
		unsigned int totalTicks(){ return ticks; }
		/** Palauttaa keskimäärin yhteen mittausväliin kuluneen ajan millisekunteina
		@returns	Ajastimen kokonaisaika jaettuna mittauspisteiden määrällä
		*/
		double averageTime(){ return (totalms / ticks); }
		/** Palauttaa edellisen mittausvälin pituuden millisekunteina
		@returns	Edellisen mittausvälin pituus
		*/
		double lastTickTime(){ return lastTick; }

	private:
		/** Ajastimen mittaama kokonaisaika
		*/
		double totalms = 0;
		/** Edellisen mittausvälin pituus
		*/
		double lastTick = 0;
		/** Mittausvälien kokonaismäärä
		*/
		unsigned int ticks = 0;
		/** Nykyisen mittausvälin käynnistysaika
		*/
		clock_time lastStart;
	};
}

#endif