/*Write a multithreaded program to add two arrays. 
Create “4” threads and print the thread number with each 
computation that is done*/

#include<stdio.h>
#include<omp.h>

#define ARRAY_SIZE 5
#define NUM_THREAD 4

int main()
{
    int array1[ARRAY_SIZE] = {1,2,3,4,5};
    int array2[ARRAY_SIZE] = {6,7,8,9,0};
    int result[ARRAY_SIZE];
    int i;

    #pragma omp parallel for shared(array1,array2) private(i)

    for(i=0;i<ARRAY_SIZE;i++)
    {
        int thread_num = omp_get_thread_num();
         result[i] = array1[i] + array2[i];
        printf("Thread %d :%d + %d = %d\n",thread_num,array1[i],array2[i],result[i]);
    }

    return 0;
}