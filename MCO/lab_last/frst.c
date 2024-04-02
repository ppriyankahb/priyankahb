/*Write a multithreaded program to multiply every element in an 
array by a constant number. 
Create “4” threads and print the thread number too with the 
results.*/

#include <stdio.h>
#include <omp.h>

#define ARRAY_SIZE 5
#define NUM_THREADS 4
#define CONSTANT 2

int main() {
    int array[ARRAY_SIZE] = {1, 2, 3, 4, 5};
    int i;

    // Set the number of threads
    omp_set_num_threads(NUM_THREADS);

    #pragma omp parallel for shared(array) private(i)
    for (i = 0; i < ARRAY_SIZE; i++) {
        int thread_num = omp_get_thread_num();
        array[i] *= CONSTANT;
        printf("Thread %d: Element %d multiplied by %d = %d\n", thread_num, i, CONSTANT, array[i]);
    }

    return 0;
}
