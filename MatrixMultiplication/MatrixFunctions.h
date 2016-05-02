/**
 *  MatrixFunctions.h
 *  ThreadedMatrixMultiplication
 *
 *  Created by Mario García on 4/30/16.
 *  Copyright © 2016 Mario García. All rights reserved.
 */
#include <stdio.h>                                    /* Used for printf */
#include <pthread.h>            /* Used for all the threads manipulation */
#include <stdlib.h>                      /* Used for the free() function */
#include "MultiplicateMatrices.h" /* Used for the mult_p type definition */

/* Create a MACRO so the user can call the function without sending the
 address of the pointer to be freed */
#define safeFree(p) saferFree((void**)&(p))
void saferFree(void ** h);
void InitializeMatrix(int ** matrix, int n);
void PrintMatrix(int * matrix, int n);
void MultiplyMatrices (int * matrix1, int * matrix2, int ** matrix3, int n, int threadID, mult_p * mult);


