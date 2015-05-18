#ifndef LOGGER_H
#define LOGGER_H

#include "stdafx.h"
#include <iostream>
#include <string>

namespace stage_common{
	class Logger{
	public:
		Logger(std::ostream& standard, std::ostream& error) : stdLog(standard), errLog(error){
		}

		void Log(std::string msg){
			stdLog << msg << std::endl;
		}

		void LogError(std::string msg){
			errLog << msg << std::endl;
		}
	private:
		std::ostream& stdLog;
		std::ostream& errLog;
	};
}

#endif