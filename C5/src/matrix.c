/*
 *         File: matrix.c
 *       Author: Steve Gunn
 *      License: MIT License
 *         Date: 27th October 2018
 *  Description: Implementation to dynamically allocate and perform operations on matrices.
 */

#include <stdio.h>
#include <stdlib.h>
#include "matrix.h"

Matrix createMatrix(const unsigned int nRows, const unsigned int nCols)
{
	Matrix mat;
	mat.rows = nRows;
	mat.cols = nCols;

	mat.element = (double **) malloc(nRows * sizeof(double *));

	for(int i=0; i<nRows; i++) {
		
		mat.element[i] = (double *)malloc(nCols * sizeof(double));
	}
	return mat;
}

Matrix createMatrixFromFile(const char *filename)
{
	Matrix m = {0, 0, NULL};
	double d;
	unsigned int i, j, nE = 0;
	int c;
	FILE *fPtr;
	
	/* Try to open the file */
	fPtr = fopen(filename, "r");
	if (!fPtr) { fprintf(stderr, "Could not open file: %s\n", filename); exit(EXIT_FAILURE); }
	
	/* Read the matrix to find out the number of columns and rows and dynamically allocate the memory */
	while(fscanf(fPtr, "%lf", &d) != EOF) {
		m.cols++;	
		while((c = fgetc(fPtr)) == ' ');
		if ((c == '\n') || (c == EOF)) 
			break;
		ungetc(c, fPtr);
	}		

	if (m.cols) {
		rewind(fPtr);
		while(fscanf(fPtr, "%lf", &d) != EOF) nE++;
		m.rows = nE / m.cols;
		m = createMatrix(m.rows, m.cols);
	}
	
	/* Do another pass to read in the elements */
	rewind(fPtr);
	for (i=0; i<m.rows; i++)
		for (j=0; j<m.cols; j++)
			fscanf(fPtr, "%lf", &m.element[i][j]);
	fclose(fPtr);
	
	return m;
}

void destroyMatrix(Matrix mat)
{
	for(int i=0; i<mat.rows; i++) {
		free(mat.element[i]);
	}
	free(mat.element);
}

void printMatrix(const Matrix mat)
{
	unsigned int i, j;
	for (i=0; i<mat.rows; i++)
		for (j=0; j<mat.cols; j++)
			printf("[%d][%d] = %f\n", i, j, mat.element[i][j]);
}

