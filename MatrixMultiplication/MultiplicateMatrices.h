/**
 *  MultiplicateMatrices.h
 *  ThreadedMatrixMultiplication
 *
 *  Created by Mario García on 4/19/16.
 *  Copyright © 2016 Mario García. All rights reserved.
 */

/* Data structure defined to access shared data */
typedef struct multiplication_ {
    pthread_mutex_t key;                          /* Synchronization variable */
    pthread_cond_t isCompleted;                    /* Signal thread completed */
} multiplication;

typedef struct multiplication_ * mult_p;
void init(mult_p * mult);
void * Production(void *arg);

