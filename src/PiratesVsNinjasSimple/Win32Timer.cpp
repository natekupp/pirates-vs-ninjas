/*
	Win32Timer.cpp

		Timer class under Microsoft Windows.

	Author:	Brett Porter
	Email: brettporter@yahoo.com
	Website: http://rsn.gamedev.net/pl3d
	Copyright (C)2000, 2001, Brett Porter. All Rights Reserved.
	This source code is released under the LGPL. See license.txt for details.

	Created: 18 July 2000
	Last Edited: 6 Febraury 2001

	Please see the file ChangeLog.html for a revision history.
*/

#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#include <Assert.h>
#include "Win32Timer.h"

#ifndef _WIN32
#	error	This file should only be used in a Microsoft Windows build.
#endif

// Disable warning about non-standard extension in Microsoft's header files
#pragma warning( disable : 4201 )
#include <mmsystem.h>
#pragma warning( default : 4201 )
#pragma comment( lib, "winmm.lib" )

Timer *Timer::getNewTimer()
{
	return new Win32Timer();
}

Win32Timer::Win32Timer()
{
	if ( QueryPerformanceFrequency(( LARGE_INTEGER* )&m_frequency ) == false )
	{
		// No performance counter available
		m_usePerformanceCounter = false;

		m_mmTimerStart = timeGetTime();
	}
	else
	{
		// Performance counter is available, use it instead of the multimedia timer
		m_usePerformanceCounter = true;

		// Get the current time and store it in pcTimerStart
		QueryPerformanceCounter(( LARGE_INTEGER* )&m_pcTimerStart );

		// Calculate the timer resolution using the timer frequency
		m_resolution = ( float )( 1.0/( double )m_frequency )*1000.0f;
	}

	m_pauseCount = 0;
	m_pauseTime = 0;
}

void Win32Timer::reset()
{
	if ( m_usePerformanceCounter == true )
		QueryPerformanceCounter(( LARGE_INTEGER* )&m_pcTimerStart );
	else
		m_mmTimerStart = timeGetTime();

	m_pauseTime = getTime();
}

double Win32Timer::getTime() const
{
	if ( m_pauseCount > 0 )
		return m_pauseTime;

	__int64 timeElapsed;

	if ( m_usePerformanceCounter == true )
	{
		QueryPerformanceCounter(( LARGE_INTEGER* )&timeElapsed );
		timeElapsed -= m_pcTimerStart;
		return timeElapsed*m_resolution;
	}
	else
	{
		timeElapsed = timeGetTime()-m_mmTimerStart;
		return ( double )timeElapsed;
	}
}

void Win32Timer::pause()
{
	if ( m_pauseCount == 0 )
		m_pauseTime = getTime();

	m_pauseCount++;
}

void Win32Timer::unpause()
{
	assert( m_pauseCount > 0 );
	m_pauseCount--;

	if ( m_pauseCount == 0 )
	{
		if ( m_usePerformanceCounter == true )
		{
			__int64 time;
			QueryPerformanceCounter(( LARGE_INTEGER* )&time );
			m_pcTimerStart = time - ( __int64 )( m_pauseTime/m_resolution );
		}
		else
		{
			m_mmTimerStart = ( unsigned )( timeGetTime() - m_pauseTime );
		}
	}
}

