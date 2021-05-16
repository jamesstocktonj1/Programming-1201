/*
 *         File: analyse.c
 *       Author: Steve Gunn
 *      License: MIT License
 *         Date: 27th October 2018
 *  Description: Program to read in a netlist file of a circuit, perform modified nodal analysis and display the result.
 */

#include <stdio.h>
#include <stdlib.h>
#include "circuit.h"

int main(int argc, char *argv[]) {
	Circuit c;
	
	if (argc == 2) {
		c = createCircuitFromFile(argv[1]);

		analyseCircuit(c);

		destroyCircuit(c);
	} 
	else 
		printf("Syntax: %s <filename>\n", argv[0]);

	return EXIT_SUCCESS;
}


