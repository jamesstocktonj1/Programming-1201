/*
 *         File: circuit.c
 *       Author: Steve Gunn
 *      License: MIT License
 *         Date: 27th October 2018
 *  Description: Implementation for modified nodal analysis on a circuit containing 
 *               voltage sources, current sources and resistors.
 */

#include <stdio.h>
#include <stdlib.h>
#include "circuit.h"

Circuit createCircuitFromFile(const char *filename)
{
	Circuit c = {0, 0, 0, 0, 0, NULL};
	Component p;
	FILE *fPtr;

	
	
	/* Try to open the file */
	fPtr = fopen(filename, "r");
	if (!fPtr) { fprintf(stderr, "Could not open file: %s\n", filename); exit(EXIT_FAILURE); }
	
	/* Read the netlist to find out how many components there are and dynamically allocate the memory */
	while(fscanf(fPtr, "%s %u %u %lf", p.name, &p.n1, &p.n2, &p.value) == 4) c.nC++; 
	c.comp = (Component *)malloc(c.nC*sizeof(Component));
	

	/* Do another pass to read in the components */
	rewind(fPtr);
	for(c.nC=0; fscanf(fPtr, "%s %u %u %lf", c.comp[c.nC].name, &c.comp[c.nC].n1, &c.comp[c.nC].n2, &c.comp[c.nC].value) == 4; c.nC++) {
		switch(c.comp[c.nC].name[0]) {
			case 'R': c.nR++; c.comp[c.nC].type = resistor; break;
			case 'V': c.nV++; c.comp[c.nC].type = voltage; break;
			case 'I': c.nI++; c.comp[c.nC].type = current; break;
			default: fprintf(stderr, "Unknown component on line %u in file %s.\n", c.nC + 1, filename); exit(EXIT_FAILURE);
		}
		if (c.comp[c.nC].n1 > c.nN) c.nN = c.comp[c.nC].n1;
		if (c.comp[c.nC].n2 > c.nN) c.nN = c.comp[c.nC].n2;
	}
	c.nN++; /* Node labelling is zero based so add one to get total number of nodes. */
	fclose(fPtr);
	return c;
}

void destroyCircuit(Circuit c)
{
	free(c.comp);
}

void analyseCircuit(const Circuit c)
{
	printf("Circuit Analysis");
	unsigned int n1, n2, i, cV;
	double value, g;
	Matrix A;
	Vector Z, X;
	
	/* Initialise matrices and vectors and zero elements */
	A = createMatrix(c.nN + c.nV, c.nN + c.nV);
	Z = createVector(c.nN + c.nV);

	/* Build nodal analysis equations */
	for(i=0, cV=0; i<c.nC; i++) {
		n1 = c.comp[i].n1;
		n2 = c.comp[i].n2;
		value = c.comp[i].value;
		switch(c.comp[i].type) {
			case resistor: 
				g = 1.0/value;
				A.element[n1][n2] -= g;
				A.element[n2][n1] -= g;
				A.element[n1][n1] += g;
				A.element[n2][n2] += g;	
			break;
			case voltage: 
				A.element[n1][cV + c.nN] = A.element[cV + c.nN][n1] = 1.0;                
				A.element[n2][cV + c.nN] = A.element[cV + c.nN][n2] = -1.0;
				Z.element[cV + c.nN] = -value;
				cV++;
			break;
			case current: 
				Z.element[n1] -= value;
				Z.element[n2] += value;
			break;
		}
	}
	
	/* Node 0 is ground and is treated differently */
	A.element[0][0] = 1.0; 
	Z.element[0] = 0.0;
	for(i=1; i<c.nN + c.nV; i++) 
		A.element[0][i] = A.element[i][0] = 0.0;


	/* Analyse and display results */
	//printMatrix(A);
	//printVector(Z);
	X = solveLinearSystem(A, Z);
	//printVector(X);
	printf("----------------------------\n");
	printf(" Voltage sources: %u\n", c.nV);
	printf(" Current sources: %u\n", c.nI);
	printf("       Resistors: %u\n", c.nR);
	printf("           Nodes: %u\n", c.nN);
	printf("----------------------------\n");
	for(i=0; i<c.nN; i++)
		printf(" Node %3u = %10.6lf V\n", i, X.element[i]);
	printf("----------------------------\n");
	if (c.nV) {
		for(i=0, cV=0; i<c.nC; i++)
			if (c.comp[i].type == voltage)
				printf(" I(%s)    = %10.6lf A\n", c.comp[i].name, X.element[c.nN + cV++]);
		printf("----------------------------\n");
	}
	
	/* Free up memory used by matrices and vectors */
	destroyMatrix(A);
	destroyVector(Z);
}

Vector solveLinearSystem(Matrix A, Vector b)
{
	/* Note: This function overwrites the contents of A and b. */
	int i, j, k;
	double mult, sum;
	Vector x = createVector(A.cols);

	/* reduce to upper triangular form */
	for (i=0; i<A.rows-1; i++)
		for (j=i+1; j<A.rows; j++) {   
			mult = -A.element[j][i]/A.element[i][i];
			for (k=i; k<A.cols; k++)
				A.element[j][k] += mult*A.element[i][k];
			b.element[j] += mult*b.element[i];
		}
	/* back substitute to find Vector x */
	for (i=A.rows-1; i>=0; i--) {
		for (j=i+1, sum = 0.0; j<A.cols; j++)
			sum += A.element[i][j] * x.element[j];
		x.element[i] = (b.element[i] - sum)/A.element[i][i];
	}
	return x;
}

