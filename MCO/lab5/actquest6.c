/*Write a program to transpose a matrix in parallel using 
OpenMP. Use shared variables for the input and output 
matrices and private variables for loop indices.*/

#include<stdio.h>
#include<omp.h>
int main()
{
    omp_set_num_threads(1);
    int matrix[10][10]={{1,2,3},{4,5,6},{7,8,9}};
    int array[10][10];
    #pragma omp parallel 
    for(int i=0;i<3;i++)
    {
        for(int j=0;j<3;j++){
            array[i][j]=matrix[j][i];
        }
    }
    for(int i=0;i<3;i++)
    {
        for(int j=0;j<3;j++){
            printf("%d\t",array[i][j]);
        }
        printf("\n");
    }

    
    return 0;
}