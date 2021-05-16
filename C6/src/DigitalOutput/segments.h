#include <avr/io.h>
/*
Array of segments where bits correspond to:

0b"abcdefgp"
*/
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