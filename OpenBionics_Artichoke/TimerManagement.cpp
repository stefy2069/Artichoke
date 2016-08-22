/*	Open Bionics - Artichoke
*	Author - Olly McBride
*	Date - December 2015
*
*	This work is licensed under the Creative Commons Attribution-ShareAlike 4.0 International License.
*	To view a copy of this license, visit http://creativecommons.org/licenses/by-sa/4.0/.
*
*	Website - http://www.openbionics.com/
*	GitHub - https://github.com/Open-Bionics
*	Email - ollymcbride@openbionics.com
*
*	TimerManagement.h
*
*/

#include <Arduino.h>			// for type definitions
#include <FingerLib.h>			// for MYSERIAL	
#include "TimerManagement.h"	// for customDelay()


static uint32_t _secondCount = 0;

void timerSetup(void)      
{
  _attachFuncToTimer(milliSecInterrupt);		// attach function to 1ms FingerLib timer interrupt
}

void milliSecInterrupt(void)
{
	static uint32_t sCounter = 0;
	
	// increment counter every millisecond
	sCounter++;
	
	// if 1000ms has passed
	if(sCounter >= 1000)
	{
		sCounter = 0;
		_secondCount ++;
	}
}

// The timer frequencies have been changed, which 'breaks' delay() and millis()
double customSeconds(void)
{
	return _secondCount;
}


bool customDelay(double delVal)
{
	static double _prevTime = 0;

	_prevTime = customMillis();

	while ((customMillis() - _prevTime) <= delVal);

	return true;
}