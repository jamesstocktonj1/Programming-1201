#include <avr/io.h>
#include <util/delay.h>
#include "et_scale.h"

#define N 2
#define MIDDLE_C 262

//time periods of popular tempos
#define BEAT_T90 750
#define BEAT_T120 500

void init_tone(void);
void tone(uint16_t frequency);

int main() {
    init_tone();
    int i=0;
    
    while(1) {

        //scale up (including top and bottom note)
        for(i=ET_SCALE_C; i<ET_SCALE_TOP; i++) {
            tone(et_scale[i]);
            _delay_ms(BEAT_T120);
        }

        //scale down (-2 so dont repeat last note and > so dont repeat bottom note)
        for(i=ET_SCALE_TOP-2; i>ET_SCALE_C; i--) {
            tone(et_scale[i]);
            _delay_ms(BEAT_T120);
        }
    }
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