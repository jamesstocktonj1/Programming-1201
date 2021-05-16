/*
 *         File: circuit.h
 *       Author: Steve Gunn
 *      License: MIT License
 *         Date: 27th October 2018
 *  Description: Data structures and interfaces for modified nodal analysis of a circuit containing 
 *               voltage sources, current sources and resistors.
 */

#ifndef _CIRCUIT_H
#define _CIRCUIT_H

#include "vector.h"
#include "matrix.h"

/* Data Structures */

typedef enum {
    resistor,
    voltage,
    current,
} CompType;
  
typedef struct {
    unsigned int n1;
    unsigned int n2;
    double value;
    CompType type;
    char name[32];
} Component;

typedef struct {
    unsigned int nV;
    unsigned int nI;
    unsigned int nR;
    unsigned int nC;
    unsigned int nN;
    Component *comp;
} Circuit;

/* Interfaces */

Circuit createCircuitFromFile(const char *filename);
void destroyCircuit(Circuit c);
void analyseCircuit(const Circuit c);
Vector solveLinearSystem(Matrix A, Vector b);

#endif
