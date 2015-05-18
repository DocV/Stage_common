#ifndef TIMER_H
#define TIMER_H

#include "stdafx.h"
#include <chrono>

typedef std::chrono::time_point<std::chrono::high_resolution_clock> clock_time;
typedef std::chrono::high_resolution_clock hrclock;

namespace stage_common{
	class Timer{
	public:
		void start(){
			lastStart = hrclock::now();
		}
		void stop(){
			clock_time end = hrclock::now();
			std::chrono::duration<double, std::milli> duration = end - lastStart;
			totalms += duration.count();
			lastTick = duration.count();
			ticks++;
		}
		void tick(){
			stop();
			start();
		}
		double totalTime(){ return totalms; }
		unsigned int totalTicks(){ return ticks; }
		double averageTime(){ return (totalms / ticks); }
		double lastTickTime(){ return lastTick; }

	private:
		double totalms = 0;
		double lastTick = 0;
		unsigned int ticks = 0;
		clock_time lastStart;
	};
}

#endif