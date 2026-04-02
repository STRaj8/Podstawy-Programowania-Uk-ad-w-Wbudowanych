#include <LPC21xx.H>
#include "led.h"
#include "keyboard.h"



void Delay (int iDelayInMs){
	int iLoopCounter;
	iDelayInMs=iDelayInMs*12000;
	for(iLoopCounter=0; iLoopCounter<iDelayInMs; iLoopCounter++)
	{	
	}
}

int main(){
	enum LedState{STOP,LED_RIGHT};
	enum LedState eLedState = LED_RIGHT;
	KeyboardInit();
 	LedInit();
	while(1){
		Delay(250);
		switch(eLedState){
			case LED_RIGHT:
				if(eKeyBoardRead() == BUTTON_0){
					eLedState = STOP;
				}
				else{
					LedStepRight();
					break;
				}
			case STOP:
				if(eKeyBoardRead() == BUTTON_1){
					LedStepRight();
					eLedState = LED_RIGHT;
				break;
				}
				else{
					break;
				}
		}		
	}
}

