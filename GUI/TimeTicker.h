#ifndef TIMETICKER_H_
#define TIMETICKER_H_

#include <windows.h>

class TimeTicker
{
protected:
	float frame_interval;
	
public:
	TimeTicker();
	virtual ~TimeTicker();
	
	void UpdateTicker();
	float GetFrameInterval();
};

#endif /*TIMETICKER_H_*/
