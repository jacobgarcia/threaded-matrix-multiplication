/**
 *  MatrixFunctions.c
 *  ThreadedMatrixMultiplication
 *
 *  Created by Mario García on 4/30/16.
 *  Copyright © 2016 Mario García. All rights reserved.
 */

#include "MatrixFunctions.h"

/*
 *
 *  Function: saferFree
 *
 *  Purpose: The free function does not check the pointer passed
 *           to see whether it is NULL and does not set the pointer
 *           to NULL before it returns. The purpose of this
 *           function is address this problems of free().
 *
 *  Parameters:
 *            Input:  A handle that points to the pointer that
 *                    is desired to free
 *
 *            Output: A clean and safe pointer to NULL. Waiting
 *                    to be destroyed by the end of the scope
 *                    of a function
 */
void saferFree(void **h) {
    /* If the handle or the pointer points to null, do nothing */
    if (h != NULL && *h != NULL) {
        free(*h);         /* Free the pointer */
        *h = NULL; /* Set the pointer to null */
    }
}

/*
 *
 *  Function: InitializeMatrix
 *
 *  Purpose: Initialize the final matrix with zeroes. The 
 *           elements of the diagonal are set to -1 
 *           in order for the sum process to know which 
 *           numbers can now be added and for which have to wait
 *
 *  Parameters:
 *            Input:  A handle that points to matrix to 
 *                    be initialized
 *
 *            Output: A matrix initialized with zeroes and
 *                    and the diagonal elements set to -1
 */
void InitializeMatrix(int ** matrix, int n) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            /* Set the elements of the diagonal to -1 in order for the sum
             to know which numbers are now completed */
            if (i == j)
                * (* matrix + (n * i) + j) = -1;
            else
                * (* matrix + (n * i) + j) = 0; /* Else initialize to 0 */
        }
    }
}

/*
 *
 *  Function: PrintMatrix
 *
 *  Purpose: Print the contents of an specified matrix
 *
 *  Parameters:
 *            Input:  A matrix with N X N dimensions
 *
 *            Output: The actual contents of the matrix
 */
void PrintMatrix(int * matrix, int n){
    for(int i = 0; i < n; i++){
        for (int j = 0; j < n; j++)
            printf("%3d ", * (matrix + (n * i) + j));
        
        printf("\n");
    }
    printf("\n");
}

/*
 *
 *  Function: MultiplyMatrices
 *
 *  Purpose: Multiply 2 square matrices and save the
 *           results in a third one
 *
 *  Parameters:
 *            Input:  2 matrices to be multiplied, a handle
 *                    that references the final matrix. The
 *                    square dimensions for the three matrices.
 *                    The thread identifier used for the matrix
 *                    displacement. Finally, a pointer to the 
 *                    structure with the synchronization
 *                    variables.
 *            Output: The product between 2 matrices with the
 *                    results stored in a third one
 */
void MultiplyMatrices (int * matrix1, int * matrix2, int ** matrix3, int n, int threadID, mult_p * mult) {
    /* Iterate over the rows */
    for(int i = 0; i < n; i++){
        int sum = 0;
        /* Calculate the value for an element of the final matrix */
        for(int j = 0; j < n; j++)
            sum += * (matrix1 + (n * threadID)+ j) * (* (matrix2 + (n * j) + i));
        
        /* CRITICAL SECTION */
        pthread_mutex_lock(&(* mult)->key);
            * (* matrix3 + (n * threadID) + i) = sum; /* Assign the calculation to a final matrix (i, j) element */
            pthread_cond_signal(&(* mult)->isCompleted); /* Signal */
        pthread_mutex_unlock(&(* mult)->key);
    }
}





