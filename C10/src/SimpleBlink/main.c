#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>


ISR(TIMER1_COMPA_vect) {
    PINB |= _BV(PB7);
}

int main() {
    
    DDRB |=  _BV(PB7);      //led as output

    //setup timer one
    TCCR1A = 0;

    TCCR1B |= _BV(WGM12);       //set to ctc mode
    TCCR1B |= _BV(CS12);        //set clock prescale to 256

    OCR1A = 18750;          //value as calculated (400ms)

    TIMSK1 |= _BV(OCIE1A);      //output compare A match interrupt
    sei();                  //enable interrupts

    while(1);
    return 0;
}