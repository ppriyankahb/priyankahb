/*Write a C program to display the current time.*/

#include<stdio.h>
#include<stdlib.h>
#include<time.h>

int main()
{
    time_t t;
    time(&t);

    printf("%s\n",ctime(&t));
    return 0;
}
