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
	enum LedState{LED_LEFT,LED_RIGHT};
	enum LedState eLedState = LED_LEFT;
	unsigned int uiMoveCounter = 0;
	KeyboardInit();
 	LedInit();
	while(1){
		Delay(250);
		switch(eLedState){
			case LED_LEFT:
				if(uiMoveCounter==0){
					LedStepLeft();
					uiMoveCounter++;
					break;
				}
				else if(uiMoveCounter==1){
					LedStepLeft();
					uiMoveCounter++;
					break;
				}
				else{
					LedStepLeft();
					uiMoveCounter=0;
					eLedState = LED_RIGHT;
					break;
				}
			case LED_RIGHT:
				if(uiMoveCounter==0){
					LedStepRight();
					uiMoveCounter++;
					break;
				}
				else if(uiMoveCounter==1){
					LedStepRight();
					uiMoveCounter++;
					break;
				}
				else{
					LedStepRight();
					uiMoveCounter=0;
					eLedState = LED_LEFT;
					break;
				}
		}		
	}
}

