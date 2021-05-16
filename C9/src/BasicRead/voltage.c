/*  Author: Steve Gunn
 * Licence: This work is licensed under the Creative Commons Attribution License. 
 *           View this license at http://creativecommons.org/about/licenses/
 *   Notes: F_CPU must be defined to match the clock frequency
 */
#include <avr/io.h>
#include <util/delay.h>
#include "debug.h"

void init_adc(void) {

	DDRA &= ~_BV(0);		//set pin 0 as output

	ADCSRA |= _BV(ADPS2) | _BV(ADPS1);
	//ADCSRA = _BV(ADPS2) | _BV(ADPS1) | _BV(ADPS0);	//set clock scaler to 128 (aprox 90kHz)
	
	
	
	ADCSRA |= _BV(ADPS2);		//sets prescaler to 16 

	ADMUX = 0;					//select channel 0
	ADMUX |= _BV(REFS0);			//AVCC reference
	ADMUX |= _BV(ADLAR);			//left to right in ADCH / ADCL

	ADCSRA |= _BV(ADIF);
	ADCSRA |= _BV(ADATE);
	ADCSRA |= _BV(ADEN);			//enagle adcs

	ADCSRA |= _BV(ADSC);	
	ADCSRB = 0;

	//ADCSRA |= _BV(ADFR);					//ADC free running mode
}

uint16_t read_adc(void)
{
	/* TODO: Acquisition code */
	uint16_t adc = 0;

	uint8_t lowerReg = ADCL;
	uint8_t upperReg = ADCH;

	//ADCSRA |= _BV(ADSC);			//start adc conversion

	//while(ADCSRA | _BV(ADIF));			//wait for conversion to stop
	

	adc = (upperReg << 2) + (lowerReg >> 6);	//read the 2 registers and bitshift to make one 10 bit value
	//printf("Register: 0x%x\t", ADMUX);
	//printf("Upper Register: %d\t", ADCH);
	//printf("Lower Register: %d\n", ADCL);

	return adc;
}

int main(void)
{
	uint16_t result = 0;
	double voltage = 0.0;
	
	init_debug_uart0();
	init_adc();
	
	for (;;) 
	{
		result = read_adc();
		//result = 512;
		voltage = (3.3 * result) / 1024;		//(adc value / 10 bit max val) * supply voltage

		//printf("%4d : %6.5fV\n", result, voltage);
		printf("0x%4x : %6.5fV\n", result, voltage);
		_delay_ms(400);
	}
}









module tristate(output logic C, input logic A, B);
	always_comb
		if (B):
			C = A;
		else:
			C = ''Z;
endmodule


module dffe(output logic Q, input logic D, enable, clock);

	always_ff @(posedge clock)
		if(enable)
			Q <= D;
endmodule