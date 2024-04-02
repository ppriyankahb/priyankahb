/*Implement a program to calculate the square of each element
in an array in parallel using OpenMP. Use shared variables 
for the input array and private variables for the parallel 
for loop indices.*/

#include<stdio.h>
#include<omp.h>

int main()
{
    int array[10]={1,2,3,4,5,6,7,8,9,10};
    int brr[10];
    #pragma omp parallel
    for(int i=0;i<10;i++){
    //printf("%d\t",array[i]);
    brr[i]=array[i]*array[i];
    }
    for(int i=0;i<10;i++)
    printf("the elements are %d\n",brr[i]);

    return 0;
}