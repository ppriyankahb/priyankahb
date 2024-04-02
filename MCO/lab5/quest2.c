#include<stdio.h>
#include<omp.h>

int main()
{
    const int N=10;
    //#pragma omp parallel for schedule(dynamic,4)

    #pragma omp parallel for schedule(guided,4)
    //#pragma omp parallel
    for(int i=0;i<N;i++)
    printf("i%d thread number is %d \n",i,omp_get_thread_num());

    return 0;
}