///////////////////////////////////////////////////////////////////////////////
//
//	TIMER.h
//	Timer class declaration
//
//	Downloaded from: www.paulsprojects.net
//
//	Copyright (c) 2006, Paul Baker
//	Distributed under the New BSD Licence.
//	http://www.paulsprojects.net/NewBSDLicense.txt
//
///////////////////////////////////////////////////////////////////////////////

#include <sys/time.h>

double timeGetTime() {
	struct timeval t;
	double t_now = 0.0;

	gettimeofday(&t, NULL);
	t_now = t.tv_sec + (t.tv_usec / 1000000.0);
	
	return t_now;
}

#ifndef TIMER_H
#define TIMER_H

class TIMER {

public:

	//constructor
	TIMER()	: isPaused(false) { Reset(); }

	//destructor
	~TIMER() {}

	void Reset() { startTime = timeGetTime(); };

	double GetTime() {
		return (isPaused)
			? pauseTime - startTime
			: (timeGetTime()) - startTime;
	};

	void Pause() {
		// Only pause if currently unpaused
		if(isPaused) return;

		isPaused = true;
		pauseTime = timeGetTime();
	};

	void Unpause() {
		//Only unpause if currently paused
		if(!isPaused) return;

		isPaused = false;
		
		//Update start time to reflect pause
		startTime += (timeGetTime() - pauseTime);
	};

protected:

	//member variables
	double startTime;
	bool isPaused;
	double pauseTime;

};

#endif	//TIMER_H