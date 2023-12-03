/*3. 
Write a program which creates two threads. Let the main thread 
display a message, "Hello, main thread here!". Also the main thread 
reads 2 integers n1 and n2 (which can range between 1 to 9) from the 
user. Main should pass n1 to thread1, and n2 to thread2. Thread1 then
displays "Hello, thread1 here!" n1 times. Thread2 displays 
"Hello,thread2 here!" n2 times. */

#include<stdio.h>
#include<stdlib.h>
#include<sys/stat.h>
#include<sys/shm.h>
#include<ctype.h>
#include<unistd.h>
#include<wait.h>
#include<pthread.h>

pthread_t t1,t2;

void* f1(void* p1)
{
    int n1=*(int*)p1;
    for(int i=0;i<n1;i++)
    {
        printf("Hello thread1 here\n");
    }
    pthread_exit(0);
}

void* f2(void* p1)
{
    int n2=*(int*)p1;
    for(int i=0;i<n2;i++)
    {
        printf("Hello thread2 here\n");
    }
    pthread_exit(0);
}

int main()
{
    int n1,n2;
    printf("hello main thread here!\n");

    printf("enter n1\n");
    scanf("%d",&n1);

    printf("enter n2\n");
    scanf("%d",&n2);

    pthread_create(&t1,NULL,f1,&n1);
    pthread_join(t1,NULL);

    pthread_create(&t2,NULL,f2,&n2);
    pthread_join(t2,NULL);

    return 0;

}