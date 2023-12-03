
/*4.
Write a program which defines a global integer array. Let the main 
read the length of the array and populate it. Next it creates 2 
threads. Let the main pass the array length to the 2 threads. One 
thread computes the sum of array elements and outputs the result. The
second thread publishes all odd numbers present in the array. {Use 
pthread_join() in the main, so that it waits for the threads to 
finish their execution.*/

#include<stdio.h>
#include<stdlib.h>
#include<sys/stat.h>
#include<sys/shm.h>
#include<ctype.h>
#include<unistd.h>
#include<wait.h>
#include<pthread.h>

pthread_t t1,t2;
int array[100];
int length;
void* f1(void* arg)
{
    int length=*(int*)arg;
    int sum=0;

    for(int i=0;i<length;i++)
    {
        sum=sum+array[i];

    }
    printf("sum is %d\n",sum);
    pthread_exit(0);

}


void* f2(void* arg1)
{
    int length=*(int*)arg1;

    for(int i=0;i<length;i++)
    {
        if(array[i]%2!=0)
        {
            printf("odd %d\t",array[i]);
        }
    }
    pthread_exit(0);
}

int main()
{
    printf("enter the length of array\n");
    scanf("%d",&length);

    printf("enter the elements to array\n");
    for(int i=0;i<length;i++)
    {
        scanf("%d",&array[i]);
    }

    pthread_create(&t1,NULL,f1,&length);
    pthread_create(&t2,NULL,f2,&length);

    pthread_join(t1,NULL);
    pthread_join(t2,NULL);

    return 0;
}