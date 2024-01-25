/*Write a C program to populate a matrix of size 20*50 by
generating random numbers in the range 101 to 201. Display
the matrix to the screen. Also determine the smallest,
largest, as well as the sum of all the elements of the
matrix and display the results to the screen. Find the
total time taken for the execution of your computations and
output the value.*/

#include<stdio.h>
#include<stdlib.h>
#include<time.h>

void matrixCalculation(int arr[20][50])
{
    int i,j;
  
    for(i=0;i<20;i++){
        for(j=0;j<50;j++)
        {
            
            arr[i][j]=rand()%101+101;
            printf("\t");
            
        }
        printf("\n");
           
    }

    for(i=0;i<20;i++){
        for(j=0;j<50;j++)
        {
            printf("%d",arr[i][j]);
            printf("\t");
        }
        printf("\n");
           
    }
}

void smallestOfMatrix(int arr[20][50])
{
    int smallest = arr[0][0];
    for(int i=0;i<20;i++){
        for(int j=0;j<50;j++)
        {
            if(arr[i][j]<smallest){
            smallest=arr[i][j];
            }
            
        }  
    }
    printf("smallest is %d\n",smallest);
    
}
void largestOfMatrix(int arr[20][50])
{
    int largest = arr[0][0];
    for(int i=0;i<20;i++){
        for(int j=0;j<50;j++)
        {
            if(arr[i][j]>largest){
            largest=arr[i][j];
            }
            
        }  
    }
    printf("largest is %d\n",largest);
    
}

void sumOfMatrix(int arr[20][50])
{
    int sum=0;
    for(int i=0;i<20;i++){
        for(int j=0;j<50;j++)
        {
            sum=sum+arr[i][j];
            
        }  
    }
    printf("sum is %d\n",sum);
    
}

int main()
{
    int arr[20][50];
    clock_t start,end;
    double cpu_time;

    start = clock();
    matrixCalculation(arr);
    smallestOfMatrix(arr);
    largestOfMatrix(arr);
    sumOfMatrix(arr);
    end = clock();

    cpu_time = ((double)(end-start))/CLOCKS_PER_SEC;
    printf("Time required to calculate the matrix sum is %f\n",cpu_time);
    return 0;
}



