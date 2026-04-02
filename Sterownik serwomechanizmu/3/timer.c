#include <LPC21xx.H>
#include "timer.h"

#define mCounterEnable (1<<0)
#define mCounterReset (1<<1)
#define mTimerInterrupt (1<<0)
#define mTimerMatch (1<<1)
#define mFlagDetector (1<<0)

void InitTimer0Match0(unsigned int iDelayTime){
	T0TCR = T0TCR | mCounterEnable;
	T0MR0 = iDelayTime *15;
	T0TCR = T0TCR | mCounterReset;
	T0TCR = T0TCR &(~mCounterReset);
	T0MCR = T0MCR | mTimerInterrupt;
	T0MCR = T0MCR | mTimerMatch;
}

void WaitOnTimer0Match0(){
	while((T0IR & mFlagDetector) == 0 ){}
	T0IR = mFlagDetector;
}
