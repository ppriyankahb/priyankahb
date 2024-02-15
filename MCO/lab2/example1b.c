// 1. (i) Write a C program to search for a given element in a
// matrix. The program should take a matrix and a target
// element as input, and it should output whether the element
// is present in the matrix or not.
// (ii) Modify your code so that you convert the code into a
// function called search().
//  Signature of search() can be as below:
//  int search(int mat[][], int rows, int cols, int
// key).
//  Let the search function return 0 on finding the key,
// and return -1 if the key is not present in the
// matrix. Write a suitable main function which invokes
// search() and observe your results.

#include<stdio.h>
#include<stdlib.h>

int row=3;
int col=3;
int matrixSearch(int matrix[rows][cols],int row,int col,int element);
int main()
{
    int element;
    
    int matrix[3][3]={{1, 2, 3},{4, 5, 6},{7, 8, 9}};
    printf("enter the element to search\n");
    scanf("%d",&element);
    matrixSearch(matrix,row,col,element);
    return 0;
}

int matrixSearch(int matrix[3][3],int row,int col,int element)
{
    int flag=0;
    for(int i=0;i<row;i++){
        for(int j=0;j<col;j++){
            if(matrix[i][j]==element)
            return 0;

        }
        
    }
    return -1;
    
}