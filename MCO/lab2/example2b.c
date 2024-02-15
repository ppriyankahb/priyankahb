/*2. (i) Write a C program to sort the elements of a matrix.
The program should take a matrix as input and display the
sorted matrix.
(ii) Modify your code so that you convert the code into a
function called sort(). Signature of matrix_sort() can be
as below:
 int sort(int mat[][], int rows, int cols).
Let the return value of sort() be zero always.
Write a suitable main() which invokes sort() and observe
your results.*/

#include<stdio.h>
#include<stdlib.h>

void sortedMatrix(int matrix[100][100],int,int);
int main()
{
    int matrix[100][100];
    int row,col;
    printf("Enter the rows and colums \n");
    scanf("%d %d",&row,&col);
    printf("Enter the matrix elements \n");
    for(int i=0;i<row;i++){
        for(int j=0;j<col;j++){
            scanf("%d",&matrix[i][j]);
        }
    }
    sortedMatrix(matrix,row,col);
    return 0;
}

void sortedMatrix(int matrix[100][100],int row,int col)
{
    int size=row*col;
    int temp[size];
    for(int i=0;i<row;i++){
        for(int j=0;j<col;j++){
            temp[i*col+j]=matrix[i][j];
        }
    }
    int temp2;
    for(int k=0;k<size;k++){
        for(int l=0;l<size-k-1;l++){
            if(temp[l]>temp[l+1])
            {
             temp2=temp[l];
             temp[l]=temp[l+1];
             temp[l+1]=temp2;
            }
        }
    }

    for(int i=0;i<row;i++){
        for(int j=0;j<col;j++){
            matrix[i][j]=temp[i*col+j];
        }
    }

    printf("Sorted matrix is:\n");
    for(int i=0;i<row;i++){
        for(int j=0;j<col;j++){
           printf("%d\t", matrix[i][j]);
           
        }
        printf("\n");
    }

}