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
	int i;
	KeyboardInit();
 	LedInit();
	while(1){
		Delay(250);
		switch(eKeyBoardRead()){
			case BUTTON_1:
				LedStepRight();
				break;
			case BUTTON_2:
				LedStepLeft();
				break;
			default:
				break;
		}
	}
}
