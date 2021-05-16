avr-gcc -mmcu=atmega644p -DF_CPU=12000000 main.c -o prog.elf
avr-objcopy -O ihex prog.elf prog.hex
avrdude -c usbasp -p m644p -U flash:w:prog.hex