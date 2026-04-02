#include <LPC21xx.H>
#include "timer_interrupts.h"
#include "led.h"

#define mCOUNTER_ENABLE (1<<0)
#define mCOUNTER_RESET  (1<<1)
#define mINTERRUPT_ON_MR0 (1<<0)
#define mRESET_ON_MR0     (1<<1)
#define mMR0_INTERRUPT    (1<<0)
#define VIC_TIMER0_CHANNEL_NR 4	
#define mIRQ_SLOT_ENABLE 0x00000020

void (*ptrTimer0InterruptFunction)(void);

__irq void Timer0IRQHandler(){

	T0IR=mMR0_INTERRUPT;
	LedStepRight();
	VICVectAddr=0x00;
}

void Timer0Interrupts_Init(unsigned int uiPeriod, void (*ptrTimer0InterruptFunction)(void)){
	
	ptrTimer0InterruptFunction=ptrTimer0InterruptFunction;
	
	VICIntEnable |= (0x1 << VIC_TIMER0_CHANNEL_NR);            		
	VICVectCntl1  = mIRQ_SLOT_ENABLE | VIC_TIMER0_CHANNEL_NR;  		
	VICVectAddr1  =(unsigned long)Timer0IRQHandler; 	   					

	T0MR0 = 15 * uiPeriod;                 	      								
	T0MCR |= (mINTERRUPT_ON_MR0 | mRESET_ON_MR0); 								

	T0TCR |=  mCOUNTER_ENABLE; 																		
}
