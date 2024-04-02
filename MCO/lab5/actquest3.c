/*Create a parallel program to calculate the factorial of a 
number using OpenMP. Use a shared variable for the result, 
and private variables for loop indices.*/

#include<stdio.h>
#include<omp.h>

int main()
{
    int fact=1,num=5;
    omp_set_num_threads(1);
    #pragma omp parallel
    for(int i=2;i<=num;i++){
    fact*=i;
    }
    printf("%d",fact);
    return 0;
}