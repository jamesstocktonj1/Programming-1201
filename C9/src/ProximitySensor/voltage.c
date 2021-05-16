/*  Author: Steve Gunn
 * Licence: This work is licensed under the Creative Commons Attribution License. 
 *           View this license at http://creativecommons.org/about/licenses/
 *   Notes: F_CPU must be defined to match the clock frequency
 */
#include <avr/io.h>
#include <util/delay.h>
#include "debug.h"

#define PROX_BOUND 868

void init_adc(void) {

	DDRA &= ~_BV(0);		//set pin 0 as output
	
	ADCSRA |= _BV(ADPS2);		//sets prescaler to 16 

	ADMUX = 0;					//select channel 0
	ADMUX |= _BV(REFS0);			//AVCC reference
	ADMUX |= _BV(ADLAR);			//left to right in ADCH / ADCL

	ADCSRA |= _BV(ADIF);
	ADCSRA |= _BV(ADATE);
	ADCSRA |= _BV(ADEN);			//enable adcs

	ADCSRA |= _BV(ADSC);	
	ADCSRB = 0;
}

void channel_adc(uint8_t n) {
	ADMUX = n;

	ADMUX |= _BV(REFS0);			//AVCC reference
	ADMUX |= _BV(ADLAR);			//left to right in ADCH / ADCL
}

uint16_t read_adc(void) {

	uint16_t adc = 0;
	uint8_t lowerReg = ADCL;
	uint8_t upperReg = ADCH;
	

	adc = (upperReg << 2) + (lowerReg >> 6);	//read the 2 registers and bitshift to make one 10 bit value

	return adc;
}

int main(void)
{
	uint16_t result = 0;
	double voltage = 0.0;

	DDRB |= _BV(PB7);		//led pin as output
	
	init_debug_uart0();
	init_adc();
	
	while(1) {

		if(read_adc() < PROX_BOUND) {
			printf("Finger Detected\n");
			PORTB |= _BV(PB7);
		}
		else {
			printf("No Finger\n");
			PORTB &= ~_BV(PB7);
		}
		_delay_ms(200);
	}
}
