
/*1. Display a welcome message in a parallel bock and observe
how many times it gets displayed.*/
#include<stdio.h>
#include<omp.h>

int main()
{

#pragma omp parallel
{
printf("welcome ");
}
return 0;
}
