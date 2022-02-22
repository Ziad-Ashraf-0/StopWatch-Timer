#include "stdint.h"
#include "gpio.h"
#include "lcd.h"
#include "delay.h"
#include "TM4C123.h"
#include "C:/Keil/EE319Kware/inc/tm4c123gh6pm.h"
#define RED 0x02
#define BLUE 0x04
#define GREEN 0x08
void Time1A_1sec_delay(void);
void SystemInit(){}
uint8 SW1,SW2;	
unsigned char i = 0;
unsigned char chr = 0;		
unsigned char sec1 = 0;
unsigned char sec2 = 0;
unsigned char min1 = 0;
unsigned char min2 = 0;
unsigned char hr1 = 0;
unsigned char hr2 = 0;	
unsigned char Character1[8] = { 0x0e,0x0e,0x04,0x04,0x1f,0x04,0x0a,0x0a};  /* Custom char set for alphanumeric LCD Module */
unsigned char Character2[8] = {0x0e,0x0e,0x15,0x0e,0x04,0x04,0x0a,0x11};  /* Custom char set for alphanumeric LCD Module */	
	
	int main(){
		
		LCD_init();
		
		GPIO_setupPinDirection(PORTF_ID,PIN0_ID,PIN_INPUT,ENABLE);
		GPIO_setupPinDirection(PORTF_ID,PIN4_ID,PIN_INPUT,ENABLE);
		GPIO_setupPinDirection(PORTF_ID,PIN1_ID,PIN_OUTPUT,DISABLE);
		GPIO_setupPinDirection(PORTF_ID,PIN2_ID,PIN_OUTPUT,DISABLE);
		GPIO_setupPinDirection(PORTF_ID,PIN3_ID,PIN_OUTPUT,DISABLE);
		
		
		/* configure PORTF4, 0 for falling edge trigger interrupt */
    GPIOF->IS  &= ~(1<<4)|~(1<<0);        /* make bit 4, 0 edge sensitive */
    GPIOF->IBE &=~(1<<4)|~(1<<0);         /* trigger is controlled by IEV */
    GPIOF->IEV &= ~(1<<4)|~(1<<0);        /* falling edge trigger */
    GPIOF->ICR |= (1<<4)|(1<<0);          /* clear any prior interrupt */
    GPIOF->IM  |= (1<<4)|(1<<0);          /* unmask interrupt */
    
    /* enable interrupt in NVIC and set priority to 3 */
    NVIC->IP[30] = 3 << 5;     /* set interrupt priority to 3 */
    NVIC->ISER[0] |= (1<<30);  /* enable IRQ30 (D30 of ISER[0]) */
		
		Time1A_1sec_delay();
		
		/* Load custom char to CGRAM */
		LCD_Custom_Char(0, Character1);		
		LCD_Custom_Char(1, Character2);
		
	  
		LCD_moveCursor(0,0);
		LCD_displayString("StopWatch Timer");
		//8-9  -  11-12  14-15
		
		LCD_moveCursor(1,4);
		LCD_displayString("00:00:00");
		
		
	
	
		while(1){
					
			/*if condition to handle time count*/
			if (i) {
			 if(chr==1){
					LCD_moveCursor(1,0);
			    LCD_displayCharacter(1);
					chr=0;
				}else{
					LCD_moveCursor(1,0);
			    LCD_displayCharacter(0);	
          chr=1;					
				}
			if (sec1 < 9) {
				sec1 += 1;
				LCD_moveCursor(1,11);
				LCD_intgerToString(sec1);
			} else {
				sec1 = 0;
				LCD_moveCursor(1,11);
				LCD_intgerToString(sec1);
				if (sec2 < 5) {
					sec2 += 1;
					LCD_moveCursor(1,10);
				  LCD_intgerToString(sec2);
				} else {
					sec1 = 0;
					sec2 = 0;
					LCD_moveCursor(1,10);
				  LCD_intgerToString(sec2);
					LCD_intgerToString(sec1);
					if (min1 < 9) {
						min1 += 1;
						LCD_moveCursor(1,8);
				    LCD_intgerToString(min1);
					} else {
						sec1 = 0;
						sec2 = 0;
						min1 = 0;
						LCD_moveCursor(1,10);
				    LCD_intgerToString(sec2);
					  LCD_intgerToString(sec1);
						LCD_moveCursor(1,8);
				    LCD_intgerToString(min1);
						if (min2 < 5) {
							min2 += 1;
							LCD_moveCursor(1,7);
				      LCD_intgerToString(min2);
						} else {
							sec1 = 0;
							sec2 = 0;
							min1 = 0;
							min2 = 0;
							LCD_moveCursor(1,10);
				      LCD_intgerToString(sec2);
					    LCD_intgerToString(sec1);
					  	LCD_moveCursor(1,7);
				      LCD_intgerToString(min2);
							LCD_intgerToString(min1);
							if (hr1 < 9) {
								hr1++;
								LCD_moveCursor(1,5);
				        LCD_intgerToString(hr1);
							} else {
								sec1 = 0;
								sec2 = 0;
								min1 = 0;
								min2 = 0;
								hr1 = 0;
								LCD_moveCursor(1,10);
				        LCD_intgerToString(sec2);
					      LCD_intgerToString(sec1);
					    	LCD_moveCursor(1,7);
				        LCD_intgerToString(min2);
						  	LCD_intgerToString(min1);
								LCD_moveCursor(1,4);
				        LCD_intgerToString(hr1);
								if (hr2 < 9) {
									hr2++;
									LCD_moveCursor(1,8);
				          LCD_intgerToString(hr2);
								} else {
									sec1 = 0;
									sec2 = 0;
									min1 = 0;
									min2 = 0;
									hr1 = 0;
									hr2 = 0;
									LCD_moveCursor(1,10);
				          LCD_intgerToString(sec2);
					        LCD_intgerToString(sec1);
					      	LCD_moveCursor(1,7);
				          LCD_intgerToString(min2);
						    	LCD_intgerToString(min1);
						  		LCD_moveCursor(1,4);
				          LCD_intgerToString(hr2);
									LCD_intgerToString(hr1);
								}
							}
						}
					}
				}
			}
			i = 0;
		}
  		
		}
				
	}
	
	
void TIMER1A_Handler()
{
	  if(TIMER1->MIS & 0x1)
		i = 1;
		TIMER1->ICR = 0x1;          /* Timer1A timeout flag bit clears*/
}
	
	
	
	void Time1A_1sec_delay(void)
{
SYSCTL->RCGCTIMER |= (1<<1);  /*enable clock Timer1 subtimer A in run mode */
TIMER1->CTL = 0; /* disable timer1 output */
TIMER1->CFG = 0x4; /*select 16-bit configuration option */
TIMER1->TAMR = 0x02; /*select periodic down counter mode of timer1 */
TIMER1->TAPR = 250-1; /* TimerA prescaler value */
TIMER1->TAILR = 64000-1 ; /* TimerA counter starting count down value 64000-1  */
TIMER1->ICR = 0x1;          /* TimerA timeout flag bit clears*/
TIMER1->IMR |=(1<<0); /*enables TimerA time-out  interrupt mask */
TIMER1->CTL |= 0x01;        /* Enable TimerA module */
NVIC->ISER[0] |= (1<<21); /*enable IRQ21 */
}



void GPIOF_Handler(void)
{	
  if (GPIOF->MIS & 0x10) /* check if interrupt causes by PF4/SW1*/
    {   
      TIMER1->CTL = 0;    /* disable timer1 output */
			GPIOF->DATA = RED;
      GPIOF->ICR |= 0x10; /* clear the interrupt flag */
     } 
    else if (GPIOF->MIS & 0x01) /* check if interrupt causes by PF0/SW2 */
    {   
			GPIOF->DATA = GREEN;
     TIMER1->CTL |= 0x01;   /* Enable TimerA module */
     GPIOF->ICR |= 0x01; /* clear the interrupt flag */
    }
}





	
	
	









	
	
	
	


	
	
	
	

