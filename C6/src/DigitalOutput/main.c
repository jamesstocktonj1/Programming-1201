#include <avr/io.h>
#include <util/delay.h>

//#include "segment.h"

//bits: 0b0gfedcba
/*
uint8_t segments[10] {
    0b00111111,
    0b00000110,
    0b01011011,
    0b01001111,
    0b01100110,
    0b01101101,
    0b01111101,
    0b00000111,
    0b01111111,
    0b01101111
};*/


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
    
    int i = 0;
    DDRA =  0xFF;

    while(1 == 1) {

        for(i=0; i<10; i++) {
            PORTA = (uint8_t)segments[i];
            _delay_ms(800);
        }
    }
    return 0;
}