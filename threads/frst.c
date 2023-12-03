/*1. 
Write a program which creates a thread. The main thread should 
publish its pid. Let the thread publish its thread id. Next the 
thread computes the sum of first twenty five numbers and outputs the 
result to the screen. {Use pthread_join() in the main, so that it 
waits for the thread to finish its execution.} 
Modify the above code such that the upper limit of the summation is 
read from the user and is passed as a parameter to the thread.
*/

#include<stdio.h>
#include<stdlib.h>
#include<sys/stat.h>
#include<sys/shm.h>
#include<ctype.h>
#include<unistd.h>
#include<wait.h>
#include<pthread.h>

void* sum(void*);
pthread_t t1;
int main()
{
    int n;

    printf("my thread id is %d\n",getpid());
    //printf("enter n\n");
    //scanf("%d",&n);

    pthread_create(&t1,NULL,sum,(void*)&n);
    pthread_join(t1,NULL);
    return 0;

    
}

void* sum(void* p1)
{
    int n=*((int*)p1);
    int sum=0;
    printf("my thread id is %lu\n",pthread_self());
    for(int i=0;i<25;i++)
    {
        sum=sum+i;
    }
    printf("sum is %d\n",sum);
    pthread_exit(0);
}