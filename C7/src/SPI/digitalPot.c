/*  Author: Steve Gunn
 * Licence: This work is licensed under the Creative Commons Attribution License.
 *          View this license at http://creativecommons.org/about/licenses/
 */


#include "spi.h"

void init_pot(void)
{
    init_spi_master();
}

void decXpot(void)
{
    spi_tx(0b00001000);
}

void incXpot(void)
{
    spi_tx(0b00000100);
}

void decYpot(void)
{
    spi_tx(0b00011000);
}

void incYpot(void)
{
    spi_tx(0b00010100);
}

void setXpot(uint8_t x)
{
    spi_tx(0b00000000);
    spi_tx(x);
}

void setYpot(uint8_t y)
{
    spi_tx(0b00010000);
    spi_tx(y);
}
