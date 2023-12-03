/*2. Write a program which creates 3 threads. 
case (i) Let the main thread input the value of n from the user. 
{Hint:- You can store n in a global variable so that it is available 
to all threads of the process} Each thread reads a message from the 
user and displays the message n times. 
case (ii) Modify your program such that the value of n is given by 
the user and is passed as a parameter to the threads.*/

#include<stdio.h>
#include<stdlib.h>
#include<sys/stat.h>
#include<sys/shm.h>
#include<ctype.h>
#include<unistd.h>
#include<wait.h>
#include<pthread.h>

void* f1(void*);
pthread_t t1,t2,t3;

int n;
int main()
{
    char msg1[100];
    char msg2[100];
    char msg3[100];

    printf("enter the value of n\n");
    scanf("%d",&n);
    printf("enter msg\n");
    scanf("%s",msg1);
    printf("enter msg\n");
    scanf("%s",msg2);
    printf("enter msg\n");
    scanf("%s",msg3);

    void* args1[2]={msg1,&n};
    void* args2[2]={msg2,&n};
    void* args3[2]={msg3,&n};
    pthread_create(&t1,NULL,f1,args1);
    pthread_create(&t2,NULL,f1,args2);
    pthread_create(&t3,NULL,f1,args3);

    pthread_join(t1,NULL);
    pthread_join(t2,NULL);
    pthread_join(t3,NULL);
    return 0;
}

void* f1(void* message)
{
    char* msg=(char*)message;

    int n=*((int*)message+1);

    for(int i=0;i<n;i++)
    {
        printf("%s\n",msg);
    }

    pthread_exit(0);
}

