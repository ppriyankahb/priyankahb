/*Implement a program to generate the Fibonacci series in 
parallel using OpenMP. Use shared variables for the result 
array and private variables for each thread's local 
variables.*/

#include<stdio.h>
#include<omp.h>
int main()
{
    int num=7;
    int frst=0,sec=1,third;
    omp_set_num_threads(1);
    #pragma omp parallel
    for(int i=0;i<=num;i++){ 
    if(i<=1)
    third=i;
    else{
        third=frst+sec;
        frst=sec;
        sec=third;
    }
    printf("%d\t",third);
    }
    
    return 0;
}