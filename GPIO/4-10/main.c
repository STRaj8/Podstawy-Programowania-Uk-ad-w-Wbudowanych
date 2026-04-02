#include <LPC21xx.H>

#define LED0_bm 0x10000
#define LED1_bm 0x20000
#define LED2_bm 0x40000
#define LED3_bm 0x80000

void Delay(unsigned int ms) 
{
	unsigned int i, j;
	for(i=0; i < ms; i++)
	{
		for(j=0; j < 7500;j++)
		{
		}
	}
 	
} 

int main()
{
 	IO1DIR = LED3_bm;
	while(1)
	{
		IO1SET = LED3_bm;
		Delay(100);
		IO1CLR = LED3_bm;
		Delay(100);
	}	
}
