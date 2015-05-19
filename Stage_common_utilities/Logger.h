#ifndef LOGGER_H
#define LOGGER_H

#include "stdafx.h"
#include <iostream>
#include <string>

namespace stage_common{
	/**Luokka, joka tarjoaa yksinkertaisen lokitoiminnon.
	*/
	class Logger{
	public:
		/** Luo uuden lokiolion
		@param standard		Minne normaalit lokiviestit kirjoitetaan
		@param error		Minne virheilmoitukset kirjoitetaan
		*/
		Logger(std::ostream& standard, std::ostream& error) : stdLog(standard), errLog(error){
		}

		/** Kirjoittaa lokiin normaalin viestin
		@param msg	Lokiin kirjoitettava viesti
		*/
		void Log(std::string msg){
			stdLog << msg << std::endl;
		}

		/** Kirjoittaa lokiin virheilmoituksen
		@param msg	Lokiin kirjoitettava viesti
		*/
		void LogError(std::string msg){
			errLog << msg << std::endl;
		}
	private:
		/**Minne normaalit lokiviestit kirjoitetaan
		*/
		std::ostream& stdLog;
		/**Minne virheilmoitukset kirjoitetaan
		*/
		std::ostream& errLog;
	};
}

#endif