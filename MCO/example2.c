/*Write a C program to generate a random number in C with
initializing the seed for the random number generator {With
every run you should observe a differnt random number}.*/

#include<stdio.h>
#include<stdlib.h>
#include<time.h>

int main()
{
    time_t t;
    time(&t);
    srand((unsigned int)t);

    printf("%d",rand());
    return 0;
}