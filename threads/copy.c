/* case 2-> passing 'n' as a parameter to the threads */

#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>

// function for each thread

void *thread_function(void *arg)
{
    char *msg = (char *)arg;
    int n = *((int *)arg + 1);

    for(int i=0; i<n; i++)
    {
        printf("%s\n", msg);
    }
    pthread_exit(NULL);
}

int main()
{
    pthread_t t1[3];
    char msg[100];
    int n;

    printf("Enter the value of n: ");
    scanf("%d", &n);

    for(int i=0; i<3; i++)
    {
        printf("Enter a message for thread %d: ", i+1);
        scanf("%s", msg);
        void *args[2] = {msg, &n};
        pthread_create(&t1[i], NULL, thread_function, args);
    }

    for(int i=0; i<3; i++)
    {
        pthread_join(t1[i], NULL);
    }

    return 0;
}