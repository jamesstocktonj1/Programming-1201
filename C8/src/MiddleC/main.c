#include <avr/io.h>
#include <util/delay.h>

#define N 2




#define MIDDLE_C 262

void init_tone(void);
void tone(uint16_t frequency);

int main() {
    init_tone();
    tone(MIDDLE_C);

    while(1);
}

void init_tone(void) {
    //D5 as output
    DDRD |= _BV(PD5);

    TCCR1A = _BV(COM1A0) | _BV(WGM10);      //set toggle on compare, phase and frequency

    TCCR1B = _BV(WGM13) | _BV(CS10);        //256 time prescaler (clock = 46,875Hz)
}

void tone(uint16_t frequency) {

   OCR1A = F_CPU / (frequency * N * 2);
}