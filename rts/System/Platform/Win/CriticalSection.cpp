/* This file is part of the Spring engine (GPL v2 or later), see LICENSE.html */

#include "CriticalSection.h"
#include <algorithm>

#include <tracy/Tracy.hpp>


CriticalSection::CriticalSection() noexcept
{
	//ZoneScoped;
	InitializeCriticalSection(&mtx);
}


CriticalSection::~CriticalSection()
{
	//ZoneScoped;
	DeleteCriticalSection(&mtx);
}


void CriticalSection::lock()
{
	//ZoneScoped;
	EnterCriticalSection(&mtx);
}


bool CriticalSection::try_lock() noexcept
{
	//ZoneScoped;
	return TryEnterCriticalSection(&mtx);
}


void CriticalSection::unlock()
{
	//ZoneScoped;
	LeaveCriticalSection(&mtx);
}



win_signal::win_signal() noexcept
: sleepers(false)
{
	//ZoneScoped;
	event = CreateEvent(NULL, true, false, NULL);
}

win_signal::~win_signal()
{
	//ZoneScoped;
	CloseHandle(event);
}

void win_signal::wait()
{
	//ZoneScoped;
	wait_for(spring_notime);
}

void win_signal::wait_for(spring_time t)
{
	//ZoneScoped;
	++sleepers;

	const DWORD timeout_milliseconds = t.toMilliSecsi();
	DWORD dwWaitResult;
	do {
		dwWaitResult = WaitForSingleObject(event, timeout_milliseconds);
	} while (dwWaitResult != WAIT_OBJECT_0 && dwWaitResult != WAIT_TIMEOUT);

	--sleepers;
}

void win_signal::notify_all(const int min_sleepers)
{
	//ZoneScoped;
	if (sleepers.load() < std::max(1, min_sleepers))
		return;

	PulseEvent(event);
}
