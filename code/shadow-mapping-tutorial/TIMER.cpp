//////////////////////////////////////////////////////////////////////////////////////////
//	TIMER.cpp
//	Functions for timer class
//	Downloaded from: www.paulsprojects.net
//	Created:	20th July 2002
//
//	Copyright (c) 2006, Paul Baker
//	Distributed under the New BSD Licence. (See accompanying file License.txt or copy at
//	http://www.paulsprojects.net/NewBSDLicense.txt)
//////////////////////////////////////////////////////////////////////////////////////////

#include <sys/time.h>

double timeGetTime() {
	struct timeval t;
	double t_now = 0.0;

	gettimeofday(&t, NULL);
	t_now = t.tv_sec + (t.tv_usec / 1000000.0);
	
	return t_now;
}

void TIMER::Reset()
{
	startTime = timeGetTime();
}

double TIMER::GetTime()
{
	if(isPaused)
		return pauseTime - startTime;
	else
		return (timeGetTime()) - startTime;
}

void TIMER::Pause()
{
	// Only pause if currently unpaused
	if(isPaused)
		return;

	isPaused = true;
	pauseTime = timeGetTime();
}

void TIMER::Unpause()
{
	//Only unpause if currently paused
	if(!isPaused)
		return;

	isPaused=false;

	//Update start time to reflect pause
	startTime += (timeGetTime() - pauseTime);
}