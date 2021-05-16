/*  Author: Steve Gunn
 * Licence: This work is licensed under the Creative Commons Attribution License. 
 *           View this license at http://creativecommons.org/about/licenses/
 *   Notes: F_CPU must be defined to match the clock frequency
 */
#include <avr/io.h>
#include <util/delay.h>
#include "debug.h"

#define PROX_BOUND 868
#define HEART_BOUND 310

#define FINGER_CHANNEL 1
#define HEART_CHANNEL 2

#define TIME_PERIOD 10

void init_adc(void) {

	DDRA &= ~_BV(0);		//set pin 0 as output
	DDRA &= ~_BV(1);
	DDRA &= ~_BV(2);
	
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

	ADCSRA |= _BV(ADSC);
}

uint16_t read_adc(void) {

	uint16_t adc = 0;
	uint8_t lowerReg = ADCL;
	uint8_t upperReg = ADCH;
	
	//while(ADCSRA & _BV(ADSC)); 

	adc = (upperReg << 2) + (lowerReg >> 6);	//read the 2 registers and bitshift to make one 10 bit value

	return adc;
}


/*uint8_t isPeak() {
	channel_adc(2);
	return (read_adc() > PROX_BOUND);
}*/

uint16_t fingerValue() {
	channel_adc(1);
	_delay_ms(1);

	return read_adc();
}

uint16_t heartValue() {
	channel_adc(2);
	_delay_ms(1);

	return read_adc();
}

int main(void)
{

	uint32_t tim = 0;
	uint8_t curPeak = 0;

	uint16_t tempHeartValue;

	double heartPeriod;
	double heartRate;

	DDRB |= _BV(PB7);		//led pin as output
	
	init_debug_uart0();
	init_adc();
	
	while(1) {

		//only prints heartbeat when proximity is ok
		if(fingerValue() < PROX_BOUND) {
			PORTB |= _BV(PB7);			//set led high

			tempHeartValue = heartValue();

			//new peak
			if((curPeak == 0) && (tempHeartValue > HEART_BOUND)) {
				curPeak = 1;
				

				heartPeriod = (tim * TIME_PERIOD);	//time period between heartbeats (ms)
				heartRate = 60000 / heartPeriod;				//60 / time period = BPM

				printf("Time Period: %f\t", heartPeriod);
				printf("Heart Rate: %f\n", heartRate);
				tim = 0;
			}
			else {
				tim++;
				//printf("No Peak");
			}

			//no longer peak
			if((curPeak != 0) && (tempHeartValue < HEART_BOUND)) {
				curPeak = 0;
				
			}
		}

		//no finger so led off
		else {
			PORTB &= ~_BV(PB7);
		}
		_delay_ms(TIME_PERIOD);
	}
}
