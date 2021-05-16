/*  Author: Klaus-Peter Zauner
 * Licence: This work is licensed under the Creative Commons Attribution License.
 *          View this license at http://creativecommons.org/about/licenses/
 *   Notes: F_CPU must be defined to match the clock frequency
 */
#include <avr/io.h>
#include <util/delay.h>

#define FREQ 4000
#define TOP 1
#define N 2



unsigned long toneClock;   /* set at timer initialisation and used
                              to calculate TOP when setting frequency */ 

void init_tone(void);
void tone(uint16_t frequency);

int main(void) {

    init_tone();
    
    for (;;) tone(FREQ);

}



/* init_tone ---
   Setup timer as a tone frequency oscillator.
*/
void init_tone(void)
{
    /******************************
    /  STUB:
    /  Replace this comment 
    /  with an implementation
    /
    ******************************/
    
    //D5 as output
    DDRD |= _BV(PD5);

    TCCR1A = _BV(COM1A0) | _BV(WG10);      //set toggle on compare, phase and frequency

    TCCR1B = _BV(WGM13) | _BV(CS10);        //256 time prescaler (clock = 46,875Hz)
}

/* tone ---
   Set oscillator output to desired frequency
*/
void tone(uint16_t frequency)
{

    /******************************
    /  STUB:
    /  Replace this comment 
    /  with an implementation
    /
    ******************************/
   
   OCR1A = F_CPU / (frequency * N * 2);
}


    //OCR1A = F_CPU / (frequency * N);
   //OCR1A = 65535;
   //ICR1 = F_CPU / (frequency * N);
   //OCR1A = 128;