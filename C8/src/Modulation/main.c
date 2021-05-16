#include <avr/io.h>
#include <util/delay.h>



#define FREQ1 4000
#define FREQ2 5000


void init_modulation(void);
void mod1(uint16_t freq);
void mod2(uint16_t freq);


int main() {
    init_modulation();




    for(;;) {
        mod1(FREQ1);
        mod2(FREQ2);
    }





}



void init_modulation() {

    //pins pd6 and pd7 as output
    DDRD |= _BV(PD6) |_BV(PD7);

    TCCR2A = _BV(COM2A0) | _BV(COM2B0) | _BV(WGM21);

    //TCCR2B = _BV(WGM22) | _BV(CS20);
    TCCR2B = _BV(CS20);

}

void mod1(uint16_t freq) {
    OCR2A = 255;
}

void mod2(uint16_t freq) {
    OCR2B = 255;
}