/**
 * \file eoTimer.h
 * \brief
 * \author EnOcean GmBH
 */

#ifndef EO_TIMER_H
#define EO_TIMER_H
#include "eoHalTypes.h"

/**
 *\class eoTimer
 *\brief tickCount helper
 */
class eoTimer
{

public:
	eoTimer();
	virtual ~eoTimer();
	/**
	 * MS tick count
	 * @return returns a ms tickCount, start time is hw dependent
	 */
	static uint32_t GetTickCount();

	/**
	 * Sleep for a specified amount of milliseconds
	 * @return returns a ms tickCount
	 */
	static void Sleep(uint32_t ms);
};

#endif // !defined(EO_TIMER_H)
