#include <stdlib.h>
#include <avr/io.h>
#include <avr/pgmspace.h>
#include <util/delay.h>				
#include <compat/deprecated.h>		
#include <avr/interrupt.h>

void LED1ON(void) {sbi(PORTC,7);}
void LED1OFF(void){cbi(PORTC,7);}
void TOGGLELED1(void) {if(bit_is_set(PORTC,7))cbi(PORTC,7); else sbi(PORTC,7);}

void LED2ON(void) {sbi(PORTC,6);}
void LED2OFF(void) {cbi(PORTC,6);}
void TOGGLELED2(void) {if(bit_is_set(PORTC,6))cbi(PORTC,6); else sbi(PORTC,6);}

char SWITCH1ON(void) {return(bit_is_clear(PIND,6));}
char SWITCH1OFF(void) {return(bit_is_set(PIND,6));}

#define LPWM	OCR1A
#define RPWM	OCR1B

int main(void)
{
	sbi(DDRC,6);
	sbi(DDRC,7);
	sbi(PORTD,6);
	sei();

	LED1ON();

	TCCR1A =  _BV(WGM10) | _BV(COM1A1) | _BV(COM1B1);    	// enable 8 bit PWM, select inverted PWM
	TCCR1B = _BV(CS11) | _BV(WGM12);
	LPWM=0;
	RPWM=0;
	sbi(DDRD,2);
	sbi(DDRD,3);
	sbi(DDRD,7);
	sbi(DDRB,3);
	sbi(DDRD,4);
	sbi(DDRD,5);

	while(1)
	{
		{						//Forward 100% speed
			sbi(PORTD,2);
			cbi(PORTD,3);
			sbi(PORTB,3);
			cbi(PORTD,7);
			LPWM=255;
			RPWM=255;		
		}
		_delay_ms(5000); 
		
		{						//Forward 50% speed
			sbi(PORTD,2);
			cbi(PORTD,3);
			sbi(PORTB,3);
			cbi(PORTD,7);
			LPWM=175;
			RPWM=175;		
		}
		_delay_ms(5000); 
		
		{						//Backward 100% speed
			cbi(PORTD,2);
			sbi(PORTD,3);
			cbi(PORTB,3);
			sbi(PORTD,7);
			LPWM=255;
			RPWM=255;			
		}
		_delay_ms(5000);
		
		{						//Backward 50% speed
			cbi(PORTD,2);
			sbi(PORTD,3);
			cbi(PORTB,3);
			sbi(PORTD,7);
			LPWM=175;
			RPWM=175;	
		}
		_delay_ms(5000);		
		
		{						//Braking mode
			sbi(PORTD,2);
			sbi(PORTD,3);
			sbi(PORTB,3);
			sbi(PORTD,7);
			LPWM=255;
			RPWM=255;		
		}
		_delay_ms(5000);		
	}
//M1 – Left motor where M1-1 – Left motor Positive terminal, M1-2 Left motor Negative terminal
//M2 – Right Motor where M2-1 – Right motor Negative terminal, M2-2 – Right motor Positive terminal
}

