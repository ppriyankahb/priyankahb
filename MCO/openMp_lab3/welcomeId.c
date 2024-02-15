
/*1. Display a welcome message in a parallel bock and observe
how many times it gets displayed.
2. Modify the above to print the thread id of the executing
thread, with each disply message.*/


#include<stdio.h>
#include<omp.h>

int main()
{

#pragma omp parallel
{
printf("welcome \n");
printf("The thread id is %d\n",omp_get_thread_num());
}
return 0;
}
