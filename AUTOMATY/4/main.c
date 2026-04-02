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
	enum LedState eLedState = STOP;
	unsigned int uiMoveCounter = 0;
	KeyboardInit();
 	LedInit();
	while(1){
		Delay(250);
		switch(eLedState){
			case LED_RIGHT:
				if(uiMoveCounter==0){
					LedStepRight();
					uiMoveCounter++;
					break;
				}
				else if(uiMoveCounter==1){
					LedStepRight();
					uiMoveCounter++;
					eLedState = STOP;
					break;
				}
			case STOP:
				if(eKeyBoardRead() == BUTTON_0){
					LedStepRight();
					uiMoveCounter=0;
					eLedState = LED_RIGHT;
				break;
				}
				else{
					break;
				}
		}		
	}
}

