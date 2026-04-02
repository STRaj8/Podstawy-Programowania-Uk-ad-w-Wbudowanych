#include <LPC21xx.H>

#define LED0_bm 0x10000
#define LED1_bm 0x20000
#define LED2_bm 0x40000
#define LED3_bm 0x80000
#define S0_bm 0x10
#define S1_bm 0x20
#define S2_bm 0x40
#define S3_bm 0x80


void Delay (int iDelayInMs){  
	int iLoopCounter;
	iDelayInMs=iDelayInMs*12000;
	for(iLoopCounter=0; iLoopCounter<iDelayInMs; iLoopCounter++)
	{
		
	}
}
void LedInit(void){
	IO1DIR = (LED0_bm|LED1_bm|LED2_bm|LED3_bm);
	IO1CLR = (LED0_bm|LED1_bm|LED2_bm|LED3_bm);
}

void LedOn(unsigned char ucLedIndeks){
	IO1CLR = (LED0_bm|LED1_bm|LED2_bm|LED3_bm);
	switch(ucLedIndeks){			
		case 0:
			IO1SET = LED0_bm;
			break;
		case 1:
			IO1SET = LED1_bm;				
			break;
		case 2:
			IO1SET = LED2_bm;
			break;
		case 3:
			IO1SET = LED3_bm;
			break;
		default:
			break;
	}
}
enum eButtonState {RELASED, PRESSED};
enum eButtonState eReadButton1(){ 
	if((IO0PIN & S0_bm)==0){
		return PRESSED;
		}
		else {
			return RELASED;
		}
}

void KeyboardInit(){
	IO0DIR = IO0DIR & (~(S0_bm|S1_bm|S2_bm|S3_bm));
}

int main(){
	KeyboardInit();
LedInit();
	while(1){
		switch(eReadButton1()){
			case RELASED:
				IO1CLR = LED1_bm;
				IO1SET = LED0_bm;
				break;
			case PRESSED:
				IO1CLR = LED0_bm;
				IO1SET = LED1_bm;
			default:
				break;
		}
	}	
}
