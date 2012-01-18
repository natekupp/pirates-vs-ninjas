/*
	CTimer.h

		This class implements a high-resolution timer.  getTicks_*S() returns the time elapsed since the class was initialized.

		Author:	Matt Pettineo
		Email:	mpettineo@gmail.com
*/

#include <windows.h> 

#ifndef CTIMER_H_
#define CTIMER_H_

class CTimer
{
public:

	CTimer ();
	~CTimer ();

	INT64 getTicks_mS ();
	INT64 getTicks_uS ();
	INT64 getTicks_nS ();

	void sleep_mS (INT64 amount);
	void sleep_uS (INT64 amount);
	void sleep_nS (INT64 amount);

	LARGE_INTEGER startTick;
	LARGE_INTEGER currentTick;
	LARGE_INTEGER CPUFrequency;

	FLOAT tickSize;

};

#endif

#ifndef PORTALIB3D_TIMER_H
#define PORTALIB3D_TIMER_H

class Timer
{
	public:
		/*	Constructor. */
		Timer();

		/*	Destructor. */
		virtual ~Timer();

		/*	Reset the timer to zero. */
		virtual void reset() = 0;

		/*	Retrieve the time in milliseconds since the timer started. */
		virtual double getTime() const = 0;

		/*	Return a new timer. IMPLEMENT THIS IN THE FILE FOR THE DERIVED CLASS. */
		static Timer *getNewTimer();

		/*	Pause this timer. */
		virtual void pause() = 0;

		/*	Unpause this timer. */
		virtual void unpause() = 0;

		/*	Pause all timers. */
		static void pauseAll();

		/*	Unpause all timers. */
		static void unpauseAll();

	private:
		struct TimerLink
		{
			Timer *m_pTimer;
			TimerLink *m_pNext;
		};

		static TimerLink *m_pTimerList;
};

#endif	// PORTALIB3D_TIMER_H