#include <avr/io.h>
#include <util/delay.h>


#define LOOP_FREQUENCY 1000

#define TIME_CONSTANT 0.02




void tone(void);

uint8_t segments[10] = {
    0b11111100,
    0b01100000,
    0b11011010,
    0b11110010,
    0b01100110,
    0b10110110,
    0b10111110,
    0b11100000,
    0b11111110,
    0b11110110,
};


int main() {
    int count = 0;
    
    DDRC = 0x00;        //port C as input
    PORTC = 0xFF;       //port C pullups

    DDRA =  0xFF;       //port A as output
    PORTA = (uint8_t)segments[0];

    while(1 == 1) {

        //if clockwise      0 - 1 
        if((PINC & _BV(0)) == 0) {
            while(PINC & _BV(1));       //wait for 1 to low

            count++;
            if(count > 9) {
                count = 0;
            }

            PORTA = (uint8_t)segments[count];
            
            tone();

            while((PINC & _BV(0)) == 0);        //wait for 0 to high
            while((PINC & _BV(1)) == 0);        //wait for 1 to high
        }

        //if anti-clockwise     1 - 0
        if((PINC & _BV(1)) == 0) {
            while(PINC & _BV(0));       //wait for 1 to high

            count--;
            if(count < 0) {
                count = 9;
            }

            PORTA = (uint8_t)segments[count];
            
            tone();

            while((PINC & _BV(1)) == 0);        //wait for 0 to high
            while((PINC & _BV(0)) == 0);        //wait for 1 to high
        }

        _delay_ms(1);
    }

    return 0;
}


void tone(void) {
    int i = 0;

    for(i=0; i<400; i++) {
        PINA |= _BV(0);
        _delay_ms(1);
    }
}