/*
 *         File: vector.h
 *       Author: Steve Gunn
 *      License: MIT License
 *         Date: 27th October 2018
 *  Description: Data structures and interfaces for operations on vectors.
 */

#ifndef _VECTOR_H
#define _VECTOR_H

/* Data structure */ 

typedef struct {
	unsigned int length;
	double *element;
} Vector;

/* Interfaces */

Vector createVector(const unsigned int nLength);
Vector createVectorFromFile(const char *filename);
void destroyVector(Vector vec);
void printVector(const Vector vec);

#endif
