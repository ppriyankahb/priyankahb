/*1. (i) Write a C program to search for a given element in a
matrix. The program should take a matrix and a target
element as input, and it should output whether the element
is present in the matrix or not.*/


#include<stdio.h>
#include<stdlib.h>
void matrixSearch(int matrix[3][3],int element);
int main()
{
    int element;
    int matrix[3][3]={{1, 2, 3},{4, 5, 6},{7, 8, 9}};
    printf("enter the element to search\n");
    scanf("%d",&element);
    matrixSearch(matrix,element);
    return 0;
}

void matrixSearch(int matrix[3][3],int element)
{
    int flag=0;
    for(int i=0;i<3;i++){
        for(int j=0;j<3;j++){
            if(matrix[i][j]==element)
            {
                printf("The element %d is present in the matrix\n",element);
                flag=1;
                break;
            }
        }
        if(flag==1)
        break;
    }
    if(flag==0)
    {
        printf("The element %d is not present in the matrix\n",element);
    }
}