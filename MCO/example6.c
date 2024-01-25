/*Write a C program to find the execution time of
outputting Hello world 10 times and 10,000 times
respectively.*/

#include<stdio.h>
#include<stdlib.h>
#include<time.h>

int printingHelloWorld(int times)
{
    for(int i=0;i<times;i++){
    printf("Hello World!\n");
    }
    return 0;
}
int main()
{
    clock_t start,end;
    double cpu_time;

    start = clock();
    printingHelloWorld(10);
    end = clock();

    cpu_time = ((double)(end-start))/CLOCKS_PER_SEC;
    printf("Time for executing Hello World! 10 times %f\n",cpu_time);

    start = clock();
    printingHelloWorld(1000);
    end = clock();

    cpu_time = ((double)(end-start))/CLOCKS_PER_SEC;
    printf("Time for executing Hello World! 10000 times %f\n",cpu_time);
    return 0;
}