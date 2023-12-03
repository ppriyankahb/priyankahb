/*5. Define a global integer matrix of size 3 * 4. Let the main thread 
populate the matrix with integers from the user. Create 4 threads. 
Each thread computes the column sum of a particular column. The main
waits for the threads to complete their execution. Finally the main 
computes the total sum of integers from the partial results given out
by the threads, and outputs the sum to the screen. 
How will your program change if there are 3 threads, each computing 
the sum of a particulr row, and finally the main thread computes the
total sum?*/

#include<stdio.h>
#include<stdlib.h>
#include<sys/stat.h>
#include<sys/shm.h>
#include<ctype.h>
#include<unistd.h>
#include<wait.h>
#include<pthread.h>

int matrix[3][4];
pthread_t t1,t2,t3,t4;

void* f1(void* p1)
{
    int row_num=*(int*)p1;
    int sum=0;

    for(int i=0;i<4;i++)
    {
        sum=sum+matrix[row_num][i];
    }
    printf("sum is %d\n",sum);
}
int main()
{
    printf("Enter the matrix elements\n");
    for(int i=0;i<3;i++)
    {
        for(int j=0;j<4;j++)
        {
            scanf("%d",&matrix[i][j]);
        }

    }
    int n1=1,n0=0,n2=2,n3=3;

    pthread_create(&t1,NULL,f1,(void*)&n0);
    pthread_create(&t2,NULL,f1,(void*)&n1);
    pthread_create(&t3,NULL,f1,(void*)&n2);
    //pthread_create(&t4,NULL,f1,(void*)&n3);

    pthread_join(t1,NULL);
    pthread_join(t2,NULL);
    pthread_join(t3,NULL);
   // pthread_join(t4,NULL);

    int tot_sum=0;
    for(int i=0;i<3;i++)
    {
        tot_sum=tot_sum+matrix[i][0];
        tot_sum=tot_sum+matrix[i][1];
        tot_sum=tot_sum+matrix[i][2];
        tot_sum=tot_sum+matrix[i][3];
    }
    printf("%d",tot_sum);

    return 0;
}