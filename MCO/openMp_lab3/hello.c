#include<stdio.h>
#include<omp.h>

int main()
{

#pragma omp parallel
{
printf("hello thread is %d\n",omp_get_thread_num());
}
return 0;
}
