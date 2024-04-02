/*Write a program to find the minimum element in an array in 
parallel using OpenMP. Use shared variables for the array 
and the minimum value, and private variables for loop 
indices.*/

#include<stdio.h>
#include<omp.h>

int main()
{
    int array[10]={1111,1112,1113,1114,1115,11,111,22,32,43};
    int min=array[0];
    #pragma omp parallel 
    for(int i=0;i<10;i++){
        if(array[i]<min)
        min=array[i];
    }
    printf("The minimum element in the array is %d",min);
    
    return 0;
}