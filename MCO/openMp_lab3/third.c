/*1. Display a welcome message in a parallel bock and observe
how many times it gets displayed.
2. Modify the above to print the thread id of the executing
thread, with each disply message.
3. Further modify the above to print the total number of
executing threads*/

#include<stdio.h>
#include<omp.h>

int main()
{
int count=0;
#pragma omp parallel
{
printf("welcome ");
printf("The thread id is %d\n",omp_get_thread_num());
count++;
}
printf("number of executed threads are : %d\n",count);
return 0;
}
