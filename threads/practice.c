/*Write a c program which create two threads. The thread work on a common square integer Matrix. 
One of the thread computes the sum of principal diagonal elements of Matrix the other thread 
computes the sum of all the principal diagonal elements of Matrix. Collect these to partial 
sum and compute the total and sum of elements also. The Matrix thread should open a file where the
 file value it produced by user and 
write a sentence of one or more lines to the file. The sentence should be taken from user*/

#include<stdio.h>
#include<stdlib.h>
#include<sys/stat.h>
#include<sys/shm.h>
#include<ctype.h>
#include<unistd.h>
#include<wait.h>
#include<pthread.h>

#define S 4
#define N 4

pthread_t t1,t2,t3;
int matrix[4][4];
void* principal(void* f1)
{
    int sum1=*(int*)f1;
    for(int i=0;i<4;i++)
    {
        for(int j=0;j<4;j++)
        {
            if(i==j)
            {
                sum1=sum1+ matrix[i][j];
            }
        }

    }
   // printf("pric sum is %d\n",sum);
   pthread_exit(0);
}

void* alldiagonal(void* f2)
{
    int sum2=*(int*)f2;
    for(int i=0;i<4;i++)
    {
        for(int j=0;j<4;j++)
        {
            if(i==j||(i+j==3))
            {
                sum2=sum2+matrix[i][j];
            }
        }

    }
    pthread_exit(0);
}


int main()
{

    //int sum1=0,sum2=0,sum3=0;


    for(int i=0;i<4;i++)
    {
        for(int j=0;j<4;j++)
        {
            scanf("%d",&matrix[i][j]);
        }

    }
    int sum1=0,sum2=0,sum3=0,sum=0;

    for(int i=0;i<4;i++)
    {
        for(int j=0;j<4;j++)
        {
                sum=sum+matrix[i][j];
            
        }

    }

    pthread_create(&t1,NULL,principal,(void*)&sum1);
    pthread_create(&t2,NULL,alldiagonal,(void*)&sum2);
    //pthread_create(&t3,NULL,oth,(void*)&sum3);
    

    pthread_join(t1,NULL);
    pthread_join(t2,NULL);
    //pthread_join(t3,NULL);

    printf("%d",sum1);
    printf("%d",sum1+sum2);
    printf("%d",sum);

    return 0;
}

