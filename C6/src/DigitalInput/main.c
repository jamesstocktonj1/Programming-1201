#include <avr/io.h>
#include <util/delay.h>



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
    
    DDRC = 0x00;
    //DDRC &= ~_BV(7);        //pin C7 as input
    PORTC |= _BV(7);       //pin C7 pullup

    DDRA =  0xFF;          //port A as output

    PORTA = (uint8_t)segments[0];

    while(1 == 1) {
        
        //when switch is pressed
        if((PINC & _BV(7)) == 0) {

            count++;
            if(count > 9) {
                count = 0;
            }

            PORTA = (uint8_t)segments[count];
            while((PINC & _BV(7)) == 0);    //wait for pin to return to high
        }
    }

    return 0;
}