#include "stdafx.h"
#include "Timer.h"

using namespace stage_common;

typedef std::chrono::high_resolution_clock hrclock;

void Timer::start(){
	lastStart = hrclock::now();
}
void Timer::stop(){
	clock_time end = hrclock::now();
	std::chrono::duration<double, std::milli> duration = end - lastStart;
	totalms += duration.count();
	lastTick = duration.count();
	ticks++;
}
void Timer::tick(){
	stop();
	start();
}