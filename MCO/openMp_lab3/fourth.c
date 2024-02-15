/*4. Create a parallel block. Compute the sum of numbers from
zero to thread_id, and output the sum to the screen. Run
your code and observe the result.*/

#include<stdio.h>
#include<omp.h>

int main()
{
int count=0;

#pragma omp parallel
{
 int thread_id = omp_get_thread_num();
printf("welcome \n");
printf("The thread id is %d\n",thread_id);
for(int i=0;i<=thread_id;i++)
{
count = count +i;
}
}
printf("sum of numbers from 0 to thread_id is : %d\n",count);
return 0;
}
