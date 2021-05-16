/*  Author: Klaus-Peter Zauner
 * Licence: This work is licensed under the Creative Commons Attribution License.
 *          View this license at http://creativecommons.org/about/licenses/
 *   Notes: F_CPU must be defined to match the clock frequency
 */
#include <stdlib.h>
#include <avr/io.h>
#include <util/delay.h>

#include "et_scale.h"


/* Pin configuration
 *       progress LED:  PB7
 * 		 Tone Output: 	PD5
 * 		 Trigger pin: 	PD4
 * 		 Volume: 		PD6, PD7
 */

#define N 2
#define TRIGGER_TIME 20

#define STEP_DELAY_MS 450



/* Inaudible frequencies used to indicate state for melody2freq: */
#define M2F_END    0
#define M2F_REST   1
#define M2F_UNKOWN 2



/* You can find music pieces in abc-notation here:

    http://abcnotation.com/search
    "Currently the index contains around 330,000 tunes
      in 140,000 files."

    The following was copied form the above site and
    "\n\" was added at each line-break to make it suitable
    to insert directly in the source code.

 */
const char melody[] ="\
X:1\n\
T: Prelude from first Cello Suite\n\
C: J.S. Bach, here transposed for mandolin\n\
M: 4/4\n\
L: 1/16\n\
K:D\n\
(DAf)e fAfA (DAf)e fAfA | (DBg)f gBgB (DBg)f gBgB |\n\
(Dcg)f gcgc (Dcg)f gcgc | (Ddf)d fdfd (Ddf)d fdfd |\n\
(DBf)e fdcd Bdcd FA^GF  | (^Gde)d eded (^Gde)d eded |\n\
(cea)^g aede cede AcBA  | (B,Fd)c dFdF (B,Fd)c dFdF |\n\
(B,^GA)B AGFE (dcB)a ^gfed | (cBA)a eace (ABc)e dcBA |\n\
^d(A=cB) cAdA f(AcB) cAdA  | (GBe)f geBA (GBe)f ge^cB |\n\
^A(cAc) ecec A(cAc) ecec   | (dcB)d cdec dcBA GFED |\n\
CGAG AGAG CGAG AGAG | (DF=c)B cFcF (DFc)B cFcF |\n\
(DGB)A BGBG (DGB)A BGBG | (D^cg)f gcgc (Dcg)f gcgc |\n\
(DAf)e fdcB AGFE DCB,A, | ^G,(EBc) dBcd G,(EBc) dBcd |\n\
=G,(EAB) cABc =G,(EAB) cABc | G,(EAc) (e^g(a2) a)EF=G ABcd |\n\
%second part\n\
(ecA)B cdef (gec)d efga | _ba^ga a=gfg gec=B AEFG |\n\
A,(EAc) efge (fdA)G FDEF | A,DFA defe ^g=fef fe^de |\n\
e=dcd dB^GF EGBd e^gag | aecB ceAc EA^GF EDCB, |\n\
A,2 (=gf edcB A)(gfe dcBA | G)(fed cBAG F)(edc BAGF |\n\
F)(dcB) [cc]e[AA]e [BB]e[cc]e [dd]e[BB]e | [cc]e[AA]e [dd]e[BB]e [cc]e[AA]e [dd]e[BB]e |\n\
[cc]e[AA]e [BB]e[cc]e [dd]e[ee]e [ff]e[AA]e | [ee]e[ff]e [gg]e[AA]e [ff]e[gg]e [aa]e[ff]e |\n\
[gg]e[ff]e [gg]e[ee]e [ff]e[ee]e [ff]e[dd]e | [ee]e[dd]e [ee]e[cc]e [dd]e[cc]e [dd]e[BB]e |\n\
ceAB =cA^cA dA^dA eA=fA | ^fAgA ^gAaA ^bA=bA=c'A^c'A |\n\
d'(fAf) d'fd'f d'(fAf) d'fd'f | d'(eAe) d'ed'e d'(eAe) d'ed'e |\n\
c'(gAg) c'gc'g c'(gAg) c'gc'g | [D16Afd'] |]\
";






void init_tone(void);
void tone(uint16_t frequency);

void init_volume();
void volume(uint8_t x);

uint16_t melody2freq(const char *abc_melody);


int main() {
    uint16_t f;
	uint8_t i = 0;

    DDRB |= _BV(PB7); /* LED */
	DDRD |= _BV(PD4);
    init_tone();

	init_volume();
	volume(i);

    
    for(;;){
    	melody2freq(melody);  /* initialise  */
    	while((f=melody2freq(NULL)) != M2F_END) {
    		if (f == M2F_UNKOWN) continue; /* skip unknown symnols */
    		tone(f);

			//short trigger pulse
			PORTD |= _BV(PD4);
			_delay_ms(TRIGGER_TIME);
			PORTD &= ~_BV(PD4);

			i++;
			volume(i);

    		_delay_ms(STEP_DELAY_MS - TRIGGER_TIME);
		PORTB ^= _BV(PB7); /* toggle LED */
    	}
    	_delay_ms(STEP_DELAY_MS);
    	_delay_ms(STEP_DELAY_MS);
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




void init_volume() {
	
	//pins pd6 and pd7 as output
    DDRD |= _BV(PD6) |_BV(PD7);

	//Fast PWM Mode 7 - set WGM20 and WGM21
	//set two outputs non-inverting - set COM2A1, COM2B1
    TCCR2A = _BV(WGM20) | _BV(WGM21) | _BV(COM2A1) | _BV(COM2B1);

	//no clock divide so frrequency of 47kHz
    TCCR2B =  _BV(CS20);

	//OCR2A = 64;
	//OCR2B = 96;

	//50% volume
	volume(127);

}

void volume(uint8_t x) {

	//sets the pulse width of x/255 * 100 %
	OCR2A = x;
	OCR2B = x;
}



/* melody2freq ---
 *   If called with a string of abc music notation
 *   initialise with this string.
 *   If called with a null-pointer, return next
 *   frequency.
 *
 *   Low frequencies which are not part of the
 *   the tone scale are returned to report state.
 *
 *   The folowing is a very crude implementation
 *   of an abc-player.
 *
 */
uint16_t melody2freq(const char *m) {
    static const char *melody;
    static uint16_t pos;
    static uint8_t scale_index;

    if(m != NULL){  /* initialization */
        melody = m;
        pos = 0;
        return M2F_END; /* to be ignored */
    }

    if(melody[++pos] == '\0') return M2F_END;


    switch( melody[pos] ) {
	case 'c':
	case 'C': {
	    scale_index = ET_SCALE_C;
	    break;
	}
	case 'd':
	case 'D': {
	    /* 2 semitones above C */
	    scale_index = ET_SCALE_C + 2;
	    break;
	}
	case 'e':
	case 'E': {
	    /* 4 semitones above C */
	    scale_index = ET_SCALE_C + 4;
	    break;
	}
	case 'f':
	case 'F': {
	    /* 5 semitones above C */
	    scale_index = ET_SCALE_C + 5;
	    break;
	}
	case 'g':
	case 'G': {
	    /* 7 semitones above C */
	    scale_index = ET_SCALE_C + 7;
	    break;
	}
	case 'a':
	case 'A': {
	    /* 9 semitones above C */
	    scale_index = ET_SCALE_C + 9;
	    break;
	}
        case 'b':
	case 'B': {
	    /* 11 semitones above C */
	    scale_index = ET_SCALE_C + 11;
	    break;
	}
        default:
	    { /* unknown symbol --> no change */
		return M2F_UNKOWN;
	    }
    }

    if(  melody[pos] > 'Z' ) {  /* lower case chars have higher ASCII codes than A-Z */
         scale_index += 12;     /* shift one octave up */
    }

    return et_scale[scale_index];
}

