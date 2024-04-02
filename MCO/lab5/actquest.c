/*Q1. 
Illustrate loop parallelism with the for loop by writing a 
program to calculate the sum of an array in parallel using 
OpenMP. (Use a shared variable for the result and private 
variables for loop indices).*/


#include<stdio.h>
#include<omp.h>
#define SIZE 10
int main()
{
    int array[SIZE];
    //int brr[SIZE];
    int i,sum=0;
    for(i=0;i<SIZE;i++){
    array[i]=i+1;
    printf("%d\t",array[i]);
    //brr[i]=i+1;
    }
    #pragma omp parallel for reduction(+:sum)
    for( i=0;i<SIZE;i++){
    //printf("%d\t",array[i]);
    sum+=array[i];
    }
    printf("the sum is %d\n",sum);

    return 0;
}
