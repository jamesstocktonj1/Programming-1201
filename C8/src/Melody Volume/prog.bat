avr-gcc -mmcu=atmega644p -DF_CPU=12000000 -Wall -Os melody.c et_scale.h -o prog.elf
avr-objcopy -O ihex prog.elf prog.hex
avrdude -c usbasp -p m644p -U flash:w:prog.hex