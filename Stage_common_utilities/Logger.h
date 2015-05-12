#ifndef LOGGER_H
#define LOGGER_H

#include "stdafx.h"
#include <iostream>

namespace stage_common{
	class Logger{
	public:
		Logger(std::ostream& standard, std::ostream& error) : stdLog(standard), errLog(error){
		}

		void Log(char* msg){
			stdLog << *msg << std::endl;
		}

		void LogError(char* msg){
			errLog << *msg << std::endl;
		}
	private:
		std::ostream& stdLog;
		std::ostream& errLog;
	};
}

#endif