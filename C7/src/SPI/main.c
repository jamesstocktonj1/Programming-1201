#include <avr/io.h>
#include <util/delay.h>

#include "digitalPot.h"




int main() {
    init_pot();

    uint8_t i=0;

    while(1) {
        setXpot(0);
        setYpot(0);
        _delay_ms(800);

        for(i=0; i<256; i++) {
            setXpot(i);
            setYpot(i);
            //incXpot();
            //incYpot();
            _delay_ms(1);
        }
    }

    return 0;
}