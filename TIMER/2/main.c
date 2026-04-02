#include <LPC21xx.H>
#include "led.h"
#include "keyboard.h"
#include "timer.h"

void Delay (int iDelayInMs){  
	int iLoopCounter;
	iDelayInMs=iDelayInMs*12000;
	for(iLoopCounter=0; iLoopCounter<iDelayInMs; iLoopCounter++)
	{
	}
}


int main(){
	InitTimer0();
	KeyboardInit();
 	LedInit();
	while(1){
		WaitOnTimer0(250000);
		LedStepLeft();
	}
}
