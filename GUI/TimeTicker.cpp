#include "TimeTicker.h"

TimeTicker::TimeTicker()
{
	this->frame_interval = 0;
}

TimeTicker::~TimeTicker()
{
}

void TimeTicker::UpdateTicker()
{
	static float frameTime = 0;
	float currentTime;
	
	currentTime = (float)::GetTickCount() / 100;
	
	this->frame_interval = currentTime - frameTime;
	
	frameTime = currentTime;
}

float TimeTicker::GetFrameInterval()
{
	return this->frame_interval;
}
