#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#define MAX_ROWS 100
#define MAX_COLS 100

// Structure to hold matrix information
typedef struct {
    int rows;
    int cols;
    int matrix[MAX_ROWS][MAX_COLS];
} Matrix;

// Structure to pass parameters to the thread
typedef struct {
    int startRow;
    int endRow;
    Matrix *matrixA;
    Matrix *matrixB;
    Matrix *result;
} ThreadArgs;

// Function to add matrices in a specified range
void *matrixAddition(void *args) {
    ThreadArgs *threadArgs = (ThreadArgs *)args;

    for (int i = threadArgs->startRow; i <= threadArgs->endRow; i++) {
        for (int j = 0; j < threadArgs->matrixA->cols; j++) {
            threadArgs->result->matrix[i][j] =
                threadArgs->matrixA->matrix[i][j] + threadArgs->matrixB->matrix[i][j];
        }
    }

    pthread_exit(NULL);
}

int main() {
    int numRows, numCols;

    // Input matrix dimensions
    printf("Enter the number of rows and columns for matrices: ");
    scanf("%d %d", &numRows, &numCols);

    if (numRows > MAX_ROWS || numCols > MAX_COLS) {
        fprintf(stderr, "Error: Matrix dimensions exceed the maximum limit.\n");
        return 1;
    }

    // Input matrices
    Matrix matrixA, matrixB, result;
    matrixA.rows = matrixB.rows = result.rows = numRows;
    matrixA.cols = matrixB.cols = result.cols = numCols;

    printf("Enter elements for matrix A:\n");
    for (int i = 0; i < numRows; i++) {
        for (int j = 0; j < numCols; j++) {
            printf("A[%d][%d]: ", i, j);
            scanf("%d", &matrixA.matrix[i][j]);
        }
    }

    printf("Enter elements for matrix B:\n");
    for (int i = 0; i < numRows; i++) {
        for (int j = 0; j < numCols; j++) {
            printf("B[%d][%d]: ", i, j);
            scanf("%d", &matrixB.matrix[i][j]);
        }
    }

    // Initialize Pthreads
    pthread_t threads[numRows];
    ThreadArgs threadArgs[numRows];

    // Divide the work among threads
    for (int i = 0; i < numRows; i++) {
        threadArgs[i].startRow = i;
        threadArgs[i].endRow = i;
        threadArgs[i].matrixA = &matrixA;
        threadArgs[i].matrixB = &matrixB;
        threadArgs[i].result = &result;
        if (pthread_create(&threads[i], NULL, matrixAddition, (void *)&threadArgs[i]) != 0) {
            fprintf(stderr, "Error: Unable to create thread.\n");
            return 1;
        }
    }

    // Wait for all threads to finish
    for (int i = 0; i < numRows; i++) {
        if (pthread_join(threads[i], NULL) != 0) {
            fprintf(stderr, "Error: Unable to join thread.\n");
            return 1;
        }
    }

    // Display the result matrix
    printf("\nMatrix A:\n");
    for (int i = 0; i < numRows; i++) {
        for (int j = 0; j < numCols; j++) {
            printf("%d\t", matrixA.matrix[i][j]);
        }
        printf("\n");
    }

    printf("\nMatrix B:\n");
    for (int i = 0; i < numRows; i++) {
        for (int j = 0; j < numCols; j++) {
            printf("%d\t", matrixB.matrix[i][j]);
        }
        printf("\n");
    }

    printf("\nResult Matrix (A + B):\n");
    for (int i = 0; i < numRows; i++) {
        for (int j = 0; j < numCols; j++) {
            printf("%d\t", result.matrix[i][j]);
        }
        printf("\n");
    }

    return 0;
}
