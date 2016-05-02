/**
 *  MultiplicateMatrices.c
 *  ThreadedMatrixMultiplication
 *
 *  Created by Mario García on 4/19/16.
 *  Copyright © 2016 Mario García. All rights reserved.
 */

#include <stdio.h>                                /* Used for printf */
#include <stdlib.h>                  /* Used for malloc & EXIT codes */
#include <pthread.h>        /* Used for all the threads manipulation */
#include "FileIO.h"    /* Used for the file access support functions */
#include "MatrixFunctions.h"

#define NUMPARAMS 2 /* This is the expected number of parameters 
                    from the command line */

int * matrix1, * matrix2, * matrix3;          /* Matrices references */

int n;                      /* Dimensions for all the matrices 
                             (N X N). This indicates the number of 
                                           threads to be created too */
long diagonalSum;                   /* Store the sum of the diagonal */
int lastChild;               /* The sum of the main diagional will be 
                                   completed by the last born thread */

mult_p mult;            /* Pointer to structure used synchronization */

int main(int argc, const char * argv[]) {
    
    FILE * fp;                                          /* Pointer to the file */
    
    pthread_t * threads;                                  /* Child threads (N) */
    int * threadID;                             /* ID specified for the thread */
    int  code;                                /* Return code from the function */
    
    /* Check if the number of parameters is correct */
    if (argc < NUMPARAMS){
        printf("Need a file with the test data\n");
        printf("Abnormal termination\n");
        exit (EXIT_FAILURE);
    } else {
        fp = fopen (argv[1], "r");            /* Open file for read operation */
        if (!fp) {                                       /* There is an error */
            printf ("The filename: %s does not exist or is corrupted\n",
                    argv[1]);
            printf ("Abnormal termination\n");
            exit (EXIT_FAILURE);                     /* Terminate the program */
        } else {
            n = GetInt(fp);                        /* Read the dimension size
                                                         for all the matrices */
            
            /* Allocate all of the matrices */
            matrix1 = (int *) malloc(sizeof(int) * n * n);
            matrix2 = (int *) malloc(sizeof(int) * n * n);
            matrix3 = (int *) malloc(sizeof(int) * n * n);
            
            /* Allocate space for the threads and the thread ID */
            threadID = (int *) malloc(sizeof(int) * n);
            threads = (pthread_t *) malloc(sizeof(pthread_t) * n);
            
            /* Create the conditional structure */
            mult = (mult_p) malloc(sizeof(multiplication));

            /* Populate the matrices with the specified 
             data in the input test file */
            for (int i = 0; i < n; i++) {
                for (int j = 0; j < n; j++)
                    * (matrix1 + (n * i) + j) = GetInt(fp);
            }
            
            for (int i = 0; i < n; i++) {
                for (int j = 0; j < n; j++)
                    * (matrix2 + (n * i) + j) = GetInt(fp);
            }
            
            fclose(fp);                          /* Close the input data file */
            
            /* Print the matrices red from the input test file */
            printf("\nMatrix A: \n");
            PrintMatrix(matrix1, n);
            
            printf("\nMatrix B: \n");
            PrintMatrix(matrix2, n);
            
            lastChild = n - 1;                        /* The last born thread */
            
            /* Initialize the final matrix elements to 0 */
            InitializeMatrix(&matrix3, n);

            /* Initialize the synchronization variables */
            init(&mult);
            
            /* Create the actual child threads */
            for(int i = 0; i < n; i++) {
                threadID[i] = i;        /* Assign a thread ID using the simple counter */
                code = pthread_create(&threads[i], NULL, Production, &threadID[i]);
                
                if (code != 0)
                    printf("Failure when creating thread with code: %d\n", code);
            }
            
            /* Wait until all threads are done */
            for(int i = 0; i < n; i++) {
                code = pthread_join(threads[i], NULL);    
                if (code != 0)
                    printf("Failure joining thread with code: %d\n", code);
            }

            /* Show the contents of the final matrix */
            printf("Final Matrix: \n");
            PrintMatrix(matrix3, n);
            
            printf("The sum of the elements of the diagonal is: %li\n", diagonalSum);

            /* Safe free the memory allocated */
            pthread_mutex_destroy(&mult->key);
            pthread_cond_destroy(&mult->isCompleted);
            safeFree(mult);
            
            safeFree(threads);
            safeFree(threadID);
            
            safeFree(matrix1);
            safeFree(matrix2);
            safeFree(matrix3);
            
            return (EXIT_SUCCESS);
        }
    }
}

void init(mult_p * mult){
    pthread_mutex_init(&(* mult)->key, NULL);
    pthread_cond_init(&(* mult)->isCompleted, NULL);
}

void * Production(void * id){
    int threadID = *((int *) id);

    /* Do the actual multiplication */
    MultiplyMatrices(matrix1, matrix2, &matrix3, n, threadID, &mult);
    
    /* If the thread is the last born child let the sum begin */
    if(threadID == lastChild) {
        pthread_mutex_lock(&mult->key);     /* Secure the crictical section */

            for (int i = 0; i < n; i++){
                /* Wait for all the diagonal to have valid numbers */
                while(* (matrix3 + (n * i) + i) == -1)
                    pthread_cond_wait(&mult->isCompleted, &mult->key);

                diagonalSum += *(matrix3 + (n * i) + i);
            }

        pthread_mutex_unlock(&mult->key);               /* Unlock the mutex */
    }
    
    return (NULL);
}
