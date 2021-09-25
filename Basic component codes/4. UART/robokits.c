#include <stdlib.h>
#include <avr/io.h>
#include <avr/pgmspace.h>
#include <util/delay.h>				
#include <compat/deprecated.h>		
#include <avr/interrupt.h>

#define UART_BAUD_RATE	115200

void LED1ON(void) {sbi(PORTC,7);}
void LED1OFF(void){cbi(PORTC,7);}
void TOGGLELED1(void) {if(bit_is_set(PORTC,7))cbi(PORTC,7); else sbi(PORTC,7);}

void LED2ON(void) {sbi(PORTC,6);}
void LED2OFF(void) {cbi(PORTC,6);}
void TOGGLELED2(void) {if(bit_is_set(PORTC,6))cbi(PORTC,6); else sbi(PORTC,6);}

char SWITCH1ON(void) {return(bit_is_clear(PIND,6));}
char SWITCH1OFF(void) {return(bit_is_set(PIND,6));}


int main(void)
{
	int i;
	sbi(DDRC,6);
	sbi(DDRC,7);
	sbi(PORTD,6);
	sei();
	
	UART_INIT(UART_BAUD_RATE);	

	LED1ON();

    UART_PRINT("\r\n\nSample code made by Robokits India for RHINO robot control board.");
	UART_PRINT("\r\n\nVisit Us at WWW.ROBOKITS.CO.IN. ");

	
	while(1)
	{
		i=UART_GETCHAR();
		if(i<256)
		{
			UART_PUTCHAR(i);
		}
	}
}

