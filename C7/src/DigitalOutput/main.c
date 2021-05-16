#include <avr/io.h>
#include <util/delay.h>
#include "debug.h"

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

#define BAUD_RATE 9600
#define ASCII_NUM_START 48

void init_uart0(void) {
    UBRR0H = (F_CPU / (BAUD_RATE * 16L) - 1) >> 8;
    UBRR0L = (F_CPU / (BAUD_RATE * 16L) - 1);
    UCSR0B = _BV(RXEN0) | _BV(TXEN0);
    UCSR0C = _BV(UCSZ00) | _BV(UCSZ01); 
}

/*
void putcharacter(char c) {
    while(!(UCSR0A & _BV(UDRE0)));
    UDR0 = c;
    return c;
}*/



int main() {
    
    int i = 0;
    DDRA =  0xFF;

    init_debug_uart0();

    while(1 == 1) {

        for(i=0; i<10; i++) {
            PORTA = (uint8_t)segments[i];
            
            printf("%d\n", i);

            _delay_ms(800);
        }
        getc();
        fprintf(stderr, "Count overflow\n");
    }
    return 0;
}