#include <avr/io.h>
#include <avr/interrupt.h>

volatile uint8_t i;


//if PD2 falls, decrement
ISR(INT0_vect) {
    PORTB |= _BV(PB7);

    if(i != 0) {
        i--;
    }
    PORTA = i;
}

//if PD3 falls, increment
ISR(INT1_vect) {
    PORTB &= ~_BV(PB7);

    if(i != 255) {
        i++;
    }
    PORTA = i;
}



int main() {
    i = 0;

    DDRA = 0xff;        //set port c as output
    //PORTC = i;
    PORTA = 0x00;

    DDRB |= _BV(PB7);		//led pin as output

    DDRD &= ~_BV(PD2);      //INT0 as input
    DDRD &= ~_BV(PD3);      //INT1 as input

    PORTD |= _BV(PD2);      //INT0, INT1 pullup
    PORTD |= _BV(PD3);


    EICRA |= _BV(ISC01);        //INT0 to falling edge
    EICRA |= _BV(ISC11);        //INT1 to falling edge

    EIMSK |= _BV(INT0);         //enable interrupts
    EIMSK |= _BV(INT1);
    sei();

    PORTA = 0x00;


    while(1);
    return 0;
}